#include "physicsubsystem.h"

#include <cmath>

void PhysicSubsystem::addObstacle(EntityId entityId, const std::shared_ptr<Rectangle> & rectangle,
                                  bool round,
                                  int resistance,
                                  bool catchBonus)
{
  _obstacles.insert({entityId, Obstacle{rectangle, round, resistance, catchBonus}});
}

void PhysicSubsystem::addDynamic(EntityId entityId, const Disc & disc)
{
  _dynamics.insert({entityId, Dynamic{disc, sf::Vector2f(0, 0), 0, true}});
}

void PhysicSubsystem::addBonus(EntityId entityId,
                               const OutsideRectangle & shape,
                               float velocity)
{
  _bonus.insert({entityId, Bonus{shape, velocity}});
}

Signal<EntityId, EntityId, sf::Vector2f> & PhysicSubsystem::onCollision()
{
  return _collisionSignal;
}

Signal<EntityId, sf::Vector2f> & PhysicSubsystem::onMove()
{
  return _moveSignal;
}

Signal<EntityId> & PhysicSubsystem::onDestroy()
{
  return _destroySignal;
}

void PhysicSubsystem::simulate(sf::Time elapsed)
{
  for(auto && dynamic : _dynamics)
  {
    if(!dynamic.second._static && dynamic.second._velocity > 0)
    {
      float residualVelocity = dynamic.second._velocity * elapsed.asSeconds();
      while(residualVelocity > 0)
      {
        CollisionDataOpt bestCollision;
        EntityId bestObstacleId(0);
        Obstacle * bestObstacle = nullptr;
        
        for(auto && obstacle : _obstacles)
        {
          auto currentCollision = obstacle.second._shape->testHit(dynamic.second._shape, dynamic.second._direction, residualVelocity);
          if(currentCollision && (!bestCollision || currentCollision > bestCollision))
          {
            bestCollision = currentCollision;
            bestObstacleId = obstacle.first;
            bestObstacle = &obstacle.second;
          }
        }
        
        if(bestCollision)
        {
          assert(bestObstacle);
          dynamic.second._shape._position = bestCollision->_position;
          if(bestObstacle->_round)
          {
            // Override bouncing direction to simulate "round" objects such as the paddle
            float angle = 3.14159265 *
              (bestCollision->_position.x - bestObstacle->_shape->getPosition().x)
              / bestObstacle->_shape->getWidth();
            dynamic.second._direction = sf::Vector2f(std::sin(angle), -std::cos(angle));            
          }
          else
          {
            dynamic.second._direction = bestCollision->_direction;
          }
          residualVelocity = bestCollision->_residualVelocity;
          
          // Send collision signal
          _collisionSignal.emit(dynamic.first, bestObstacleId, bestCollision->_position);

          // If obstacle is destructible, check if it should be destroyed
          if(bestObstacle->_resistance > 1)
          {
            --bestObstacle->_resistance;
          }
          else if(bestObstacle->_resistance == 1)
          {
            _destroySignal.emit(bestObstacleId);
            _obstacles.erase(bestObstacleId);
          }
        }
        else
        {
          dynamic.second._shape._position += dynamic.second._direction * residualVelocity;
          residualVelocity = 0;
        }

        if(residualVelocity == 0)
        {
          // Send change of position signal
          _moveSignal.emit(dynamic.first, dynamic.second._shape._position);
        }
      }
    }
  }

  for(auto && bonus : _bonus)
  {
    for(auto && obstacle : _obstacles)
    {
      if(obstacle.second._catchBonus && obstacle.second._shape->testHit(bonus.second._shape))
      {
        _collisionSignal.emit(bonus.first, obstacle.second._catchBonus, sf::Vector2f());
        _destroySignal.emit(bonus.first);
        _bonus.erase(bonus.first);
      }
    }
  }
}

void PhysicSubsystem::moveObstacle(EntityId entityId, const sf::Vector2f & position)
{
  auto it = _obstacles.find(entityId);
  if(it != _obstacles.end())
  {
    it->second._shape->setPosition(position);
    _moveSignal.emit(it->first, position);
  }
}

void PhysicSubsystem::moveDynamic(EntityId entityId, const sf::Vector2f & position)
{
  auto it = _dynamics.find(entityId);
  if(it != _dynamics.end())
  {
    it->second._shape._position = position;
    _moveSignal.emit(it->first, position);
  }
}

bool PhysicSubsystem::isStatic(EntityId entityId) const
{
  auto it = _dynamics.find(entityId);
  if(it != _dynamics.end())
  {
    return it->second._static;
  }
  else
  {
    // Return any value
    return false;
  }
}

void PhysicSubsystem::setStatic(EntityId entityId)
{
  auto it = _dynamics.find(entityId);
  if(it != _dynamics.end())
  {
    it->second._static = true;
  }
}

void PhysicSubsystem::setDynamic(EntityId entityId, const sf::Vector2f & direction)
{
  auto it = _dynamics.find(entityId);
  if(it != _dynamics.end())
  {
    it->second._direction = normalize(direction);
    it->second._velocity = norm(direction);
    it->second._static = false;
  }
}

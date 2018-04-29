#include "physicsubsystem.h"


void PhysicSubsystem::addObstacle(EntityId entityId, const Rectangle & rectangle)
{
  _obstacles.insert({entityId, rectangle});
}

void PhysicSubsystem::addDynamic(EntityId entityId, const Disc & disc)
{
  _dynamics.insert({entityId, Dynamic{disc, sf::Vector2f(0, 0), 0, true}});
}

Signal<EntityId, EntityId> & PhysicSubsystem::onCollision()
{
  return _collisionSignal;
}

Signal<EntityId, sf::Vector2f> & PhysicSubsystem::onMove()
{
  return _moveSignal;
}

void PhysicSubsystem::simulate(sf::Time elapsed)
{
  std::vector<std::pair<EntityId, EntityId> > collisions;
  std::vector<std::pair<EntityId, sf::Vector2f> > changeOfPositions;
  
  for(auto && dynamic : _dynamics)
  {
    if(!dynamic.second._static && dynamic.second._velocity > 0)
    {
      float residualVelocity = dynamic.second._velocity * elapsed.asSeconds();
      while(residualVelocity > 0)
      {
        CollisionDataOpt bestCollision;
        EntityId obstacleId(0);
        
        for(auto && obstacle : _obstacles)
        {
          auto currentCollision = obstacle.second.testHit(dynamic.second._shape, dynamic.second._direction, residualVelocity);
          if(currentCollision && (!bestCollision || currentCollision > bestCollision))
          {
            bestCollision = currentCollision;
            obstacleId = obstacle.first;
          }
        }
        
        if(bestCollision)
        {
          dynamic.second._shape._position = bestCollision->_position;
          dynamic.second._direction = bestCollision->_direction;
          residualVelocity = bestCollision->_residualVelocity;
          collisions.push_back({dynamic.first, obstacleId});
        }
        else
        {
          dynamic.second._shape._position += dynamic.second._direction * residualVelocity;
          residualVelocity = 0;
        }

        if(residualVelocity == 0)
        {
          changeOfPositions.push_back({dynamic.first, dynamic.second._direction});
        }
      }
    }
  }
  
  // Raise the events when the simulation is complete
  for(auto && collision : collisions)
  {
    _collisionSignal.emit(collision.first, collision.second);
  }
  for(auto && changeOfPosition : changeOfPositions)
  {
    _moveSignal.emit(changeOfPosition.first, changeOfPosition.second);
  }
}

void PhysicSubsystem::onMove(EntityId entityId, const sf::Vector2f & position)
{
  auto it = _dynamics.find(entityId);
  if(it != _dynamics.end())
  {
    it->second._shape._position = position;
  }
  
  auto it2 = _obstacles.find(entityId);
  if(it2 != _obstacles.end())
  {
    it2->second.setPosition(position);
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

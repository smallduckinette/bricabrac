#include "ball.h"
#include "item.h"

Ball::Ball(float initialVelocity,
           float maxVelocity,
           float acceleration):
  _position(350, 550),
  _direction(normalize(sf::Vector2f(1, -1))),
  _velocity(initialVelocity),
  _maxVelocity(maxVelocity),
  _acceleration(acceleration)
{
  if(!_texture.loadFromFile("../resources/bille.png"))
    throw std::runtime_error("Cannot find bille.png");
  _texture.setSmooth(true);
  
  setTexture(_texture);
  setOrigin(sf::Vector2f(10, 10));
  setPosition(_position.x, _position.y);
}

bool Ball::update(sf::Time elapsed, std::list<std::shared_ptr<Item> > & world)
{
  float residualVelocity = _velocity * elapsed.asSeconds();
  while(residualVelocity > 0)
  {
    CollisionDataOpt bestCollision;
    
    Disc disc(_position, 10);
    
    auto it = world.begin();
    auto end = world.end();
    auto bestItem = end;
    for(; it != end; ++it)
    {
      auto && item = *it;
      auto currentCollision = item->testCollision(disc, _direction, residualVelocity);
      if(currentCollision && (!bestCollision || currentCollision > bestCollision))
      {
        bestCollision = currentCollision;
        bestItem = it;
      }
    }
    if(bestCollision)
    {
      _position = bestCollision->_position;
      _direction = bestCollision->_direction;
      residualVelocity = bestCollision->_residualVelocity;
      if((*bestItem)->commitCollision())
      {
        world.erase(bestItem);
      }

      // There was a collision, so let's accelerate
      if(_velocity < _maxVelocity)
      {
        _velocity += _acceleration;
      }
    }
    else
    {
      _position = _position + _direction * residualVelocity;
      residualVelocity = 0;
    }
  }
  
  setPosition(_position.x, _position.y);
  
  return (_position.y > 600);
}

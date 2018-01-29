#include "ball.h"
#include "item.h"

Ball::Ball():
  _position(350, 550),
  _direction(normalize(sf::Vector2f(1, -1))),
  _velocity(300)
{
  if(!_texture.loadFromFile("../resources/bille.png"))
    throw std::runtime_error("Cannot find bille.png");
  _texture.setSmooth(true);
  
  setTexture(_texture);
  setOrigin(sf::Vector2f(10, 10));
  setPosition(_position.x, _position.y);
}

void Ball::update(sf::Time elapsed, std::list<std::shared_ptr<Item> > & world)
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
    }
    else
    {
      _position = _position + _direction * residualVelocity;
      residualVelocity = 0;
    }
  }
  
  setPosition(_position.x, _position.y);
}

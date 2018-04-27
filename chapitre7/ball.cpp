#include "ball.h"
#include "item.h"

Ball::Ball(float initialVelocity,
           float maxVelocity,
           float acceleration):
  _direction(normalize(sf::Vector2f(1, -1))),
  _initialVelocity(initialVelocity),
  _velocity(initialVelocity),
  _maxVelocity(maxVelocity),
  _acceleration(acceleration),
  _sticky(true)
{
  if(!_texture.loadFromFile("../resources/bille.png"))
    throw std::runtime_error("Cannot find bille.png");
  _texture.setSmooth(true);
  
  setTexture(_texture);
  setOrigin(sf::Vector2f(10, 10));
  setPosition(350, 550);
}

bool Ball::update(sf::Time elapsed, std::list<std::shared_ptr<Item> > & world)
{
  if(isSticky())
  {
    return false;
  }
  else
  {
    float residualVelocity = _velocity * elapsed.asSeconds();
    while(residualVelocity > 0)
    {
      CollisionDataOpt bestCollision;
    
      Disc disc(getPosition(), 10);
    
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
        setPosition(bestCollision->_position);
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
        setPosition(getPosition() + _direction * residualVelocity);
        residualVelocity = 0;
      }
    }
    
    return (getPosition().y > 600);
  }
}

void Ball::setSticky(bool sticky)
{
  _sticky = sticky;
}

bool Ball::isSticky() const
{
  return _sticky;
}

void Ball::reset(const sf::Vector2f & position)
{
  setPosition(position);
  _direction = normalize(sf::Vector2f(1, -1));
  _velocity = _initialVelocity;
  _sticky = true;
}

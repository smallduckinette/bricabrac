#include "ball.h"
#include "item.h"

Ball::Ball():
  _position(350, 550),
  _direction(normalize(sf::Vector2f(1, -1))),
  _velocity(200)
{
  if(!_texture.loadFromFile("../resources/bille.png"))
    throw std::runtime_error("Cannot find bille.png");
  _texture.setSmooth(true);
  
  setTexture(_texture);
  setOrigin(sf::Vector2f(10, 10));
  setPosition(_position.x, _position.y);
}

void Ball::update(sf::Time elapsed, const std::vector<std::shared_ptr<Item> > & world)
{
  float residualVelocity = _velocity * elapsed.asSeconds();
  while(residualVelocity > 0)
  {
    CollisionDataOpt c;
    Disc disc(_position, 10);
    
    for(auto && item : world)
    {
      c = c ^ item->testCollision(disc, _direction, residualVelocity);
      
    }
    if(c)
    {
      _position = c->_position;
      _direction = c->_direction;
      residualVelocity = c->_residualVelocity;
    }
    else
    {
      _position = _position + _direction * residualVelocity;
      residualVelocity = 0;
    }
  }
  
  setPosition(_position.x, _position.y);
}

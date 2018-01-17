#include "paddle.h"

Paddle::Paddle()
{
  if(!_texture.loadFromFile("../resources/plateau.png"))
    throw std::runtime_error("Cannot find plateau.png");
  _texture.setSmooth(true);
  
  setTexture(_texture);
  setScale(sf::Vector2f(0.5, 0.5));
  setOrigin(sf::Vector2f(60, 0));
  setPosition(350, 560);
}

void Paddle::move(int x)
{
  setPosition(x, 560);
}

boost::optional<CollisionData> Paddle::testCollision(const Disc & disc,
                                                     const sf::Vector2f & direction,
                                                     float velocity) const
{
  return Rectangle(getPosition() + sf::Vector2f(-30, 0),
                   getPosition() + sf::Vector2f(30, 20)).testHit(disc, direction, velocity);
}

bool Paddle::commitCollision()
{
  return false;
}

void Paddle::draw(sf::RenderWindow * window)
{
  window->draw(*this);
}

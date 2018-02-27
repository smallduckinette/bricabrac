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

  if(!_soundBuffer.loadFromFile("../resources/bong.flac"))
    throw std::runtime_error("Cannot find bong.flac");
  _sound.setBuffer(_soundBuffer);
}

void Paddle::move(int x)
{
  setPosition(x, 560);
}

boost::optional<CollisionData> Paddle::testCollision(const Disc & disc,
                                                     const sf::Vector2f & direction,
                                                     float velocity) const
{
  auto c = Rectangle(getPosition() + sf::Vector2f(-30, 0),
                     getPosition() + sf::Vector2f(30, 20)).testHit(disc, direction, velocity);

  // Override the direction to depend on the hit position on the paddle
  if(c && c->_direction.y < 0)
  {
    float angle = 3.14159265 * (c->_position.x - getPosition().x) / 60;
    c->_direction = sf::Vector2f(std::sin(angle), -std::cos(angle));
  }

  return c;
}

bool Paddle::commitCollision()
{
  _sound.setPosition((getPosition().x - 400.0) / 400, 0, 0.1);
  _sound.play();
  return false;
}

void Paddle::draw(sf::RenderWindow * window)
{
  window->draw(*this);
}

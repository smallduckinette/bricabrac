#include "brick.h"
#include "collisiondata.h"
#include "physics.h"

Brick::Brick(const sf::Texture & texture, int x, int y):
  _x(x),
  _y(y)
{
  setTexture(texture);
  setPosition(x, y);
}

boost::optional<CollisionData> Brick::testCollision(const Disc & disc,
                                                    const sf::Vector2f & direction,
                                                    float velocity) const
{
  return Rectangle(sf::Vector2f(_x, _y),
                   sf::Vector2f(_x + 50, _y + 30)).testHit(disc, direction, velocity);
}

bool Brick::commitCollision()
{
  return true;
}

void Brick::draw(sf::RenderWindow * window)
{
  window->draw(*this);
}

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

boost::optional<CollisionData> Brick::testCollision(const Disc &,
                                                    const sf::Vector2f &,
                                                    float) const
{
  return {};
}

bool Brick::commitCollision()
{
  return false;
}

void Brick::draw(sf::RenderWindow * window)
{
  window->draw(*this);
}

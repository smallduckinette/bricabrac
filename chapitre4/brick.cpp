#include "brick.h"
#include "collisiondata.h"
#include "physics.h"

Brick::Brick(const sf::Texture & texture, const std::shared_ptr<sf::Sound> & bing, int x, int y):
  _x(x),
  _y(y),
  _bing(bing)
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
  _bing->setPosition((getPosition().x - 400.0) / 400, 0, 0.1);
  _bing->play();
  return true;
}

void Brick::draw(sf::RenderWindow * window)
{
  window->draw(*this);
}

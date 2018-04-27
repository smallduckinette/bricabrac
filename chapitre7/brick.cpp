#include "brick.h"
#include "collisiondata.h"
#include "physics.h"

Brick::Brick(const sf::Texture & texture, int textureIndex, const std::shared_ptr<sf::Sound> & bing, int x, int y):
  _bing(bing)
{
  setTexture(texture);
  setPosition(x, y);
  setTextureRect(sf::IntRect(0, (textureIndex - 1) * 30, 50, 30));
}

boost::optional<CollisionData> Brick::testCollision(const Disc & disc,
                                                    const sf::Vector2f & direction,
                                                    float velocity) const
{
  return Rectangle(getPosition(),
                   getPosition() + sf::Vector2f(50, 30)).testHit(disc, direction, velocity);
}

bool Brick::commitCollision()
{
  playSound();
  return true;
}

void Brick::playSound()
{
  _bing->setPosition((getPosition().x - 400.0) / 400, 0, 0.1);
  _bing->play();  
}

bool Brick::requiredToWin() const
{
  // Bricks always need to be destroyed in order to win.
  // If we ever have unbreakable bricks, they would need
  // to return false
  return true;
}

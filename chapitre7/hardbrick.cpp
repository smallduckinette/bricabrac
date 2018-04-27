#include "hardbrick.h"


HardBrick::HardBrick(const sf::Texture & texture, int textureIndex, const std::shared_ptr<sf::Sound> & bing, int x, int y):
  Brick(texture, textureIndex, bing, x, y),
  _hardness(3)
{
}

bool HardBrick::commitCollision()
{
  --_hardness;
  if(_hardness == 0)
  {
    return Brick::commitCollision();
  }
  else
  {
    playSound();
    setTextureRect(sf::IntRect(0, getTextureRect().top + 30, 50, 30));
    return false;
  }
}

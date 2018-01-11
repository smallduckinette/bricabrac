#include "brick.h"


Brick::Brick(const sf::Texture & texture, int x, int y)
{
  setTexture(texture);
  setPosition(x, y);
}

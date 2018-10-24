#include "powerbrick.h"


PowerBrick::PowerBrick(const sf::Texture & texture,
                       int textureIndex,
                       int x,
                       int y,
                       float fallRate):
  _fallRate(fallRate)
{
  setTexture(texture);
  setPosition(x, y);
  setTextureRect(sf::IntRect(0, (textureIndex - 1) * 30, 50, 30));
}

bool PowerBrick::update(sf::Time elapsed)
{
  setPosition(getPosition() + sf::Vector2f(0, _fallRate * elapsed.asSeconds()));
  return false;
}

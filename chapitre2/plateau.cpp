#include "plateau.h"

Plateau::Plateau()
{
  if(!_texture.loadFromFile("../resources/plateau.png"))
    throw std::runtime_error("Cannot find plateau.png");
  _texture.setSmooth(true);
  
  setTexture(_texture);
  setScale(sf::Vector2f(0.5, 0.5));
  setOrigin(sf::Vector2f(60, 0));
  setPosition(350, 560);
}

void Plateau::move(int x)
{
  setPosition(x, 560);
}

#include "lifes.h"



Lifes::Lifes(unsigned int lifeCount):
  _lifeCount(lifeCount),
  _sprite(std::make_shared<sf::Sprite>())
{
  if(!_texture.loadFromFile("../resources/plateau.png"))
    throw std::runtime_error("Cannot find plateau.png");
  _texture.setSmooth(true);
  
  _sprite->setTexture(_texture);
  _sprite->setScale(sf::Vector2f(0.5, 0.5));
}
  
void Lifes::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for(unsigned int index = 0; index < _lifeCount; ++index)
  {
    _sprite->setPosition(10, 10 + index * 30);
    target.draw(*_sprite, states);
  }
}

bool Lifes::decrement()
{
  if(_lifeCount > 0)
  {
    --_lifeCount;
  }
  
  return _lifeCount == 0;
}

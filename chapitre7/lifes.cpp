#include "lifes.h"

#include "gameplay.h"

Lifes::Lifes(const std::shared_ptr<Gameplay> & gameplay):
  _gameplay(gameplay),
  _sprite(std::make_shared<sf::Sprite>())
{
  if(!_texture.loadFromFile("../resources/plateau.png"))
    throw std::runtime_error("Cannot find plateau.png");
  _texture.setSmooth(true);
  
  _sprite->setTexture(_texture);
}
  
void Lifes::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for(unsigned int index = 0; index < _gameplay->getLives(); ++index)
  {
    _sprite->setPosition(10, 10 + index * 30);
    target.draw(*_sprite, states);
  }
}

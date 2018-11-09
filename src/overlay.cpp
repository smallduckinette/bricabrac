#include "overlay.h"

#include "gameplay.h"

Overlay::Overlay(const std::shared_ptr<Gameplay> & gameplay):
  _gameplay(gameplay),
  _lifeSprite(std::make_shared<sf::Sprite>())
{
  if(!_lifeTexture.loadFromFile("resources/plateau.png"))
    throw std::runtime_error("Cannot find plateau.png");
  _lifeTexture.setSmooth(true);
  
  _lifeSprite->setTexture(_lifeTexture);

  if(!_failMessage.loadFromFile("resources/fail.png"))
    throw std::runtime_error("Cannot find fail.png");
  _failMessage.setSmooth(true);
}

void Overlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for(unsigned int index = 0; index < _gameplay->getLives(); ++index)
  {
    _lifeSprite->setPosition(10, 10 + index * 30);
    target.draw(*_lifeSprite, states);
  }
  for(auto && sprite : _overlaySprites)
  {
    target.draw(*sprite, states);
  }
}

void Overlay::onFailure()
{
  auto sprite = std::make_shared<sf::Sprite>();
  sprite->setTexture(_failMessage);
  sf::Vector2u msgPosition = sf::Vector2u(800, 600) / 2u - _failMessage.getSize() / 2u;
  sprite->setPosition(msgPosition.x, msgPosition.y);
  
  _overlaySprites.push_back(sprite);
}

void Overlay::clear()
{
  _overlaySprites.clear();
}

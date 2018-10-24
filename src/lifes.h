#ifndef __CHAPITRE6_LIFES_H__
#define __CHAPITRE6_LIFES_H__

#include <memory>

#include <SFML/Graphics.hpp>

class Gameplay;

class Lifes : public sf::Drawable
{
public:
  Lifes(const std::shared_ptr<Gameplay> & gameplay);
  
  /// Implementation of sf::Drawable interface
  void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
  
private:
  std::shared_ptr<Gameplay> _gameplay;
  
  sf::Texture _texture;
  std::shared_ptr<sf::Sprite> _sprite;
};

#endif

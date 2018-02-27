#ifndef __CHAPITRE6_LIFES_H__
#define __CHAPITRE6_LIFES_H__

#include <memory>

#include <SFML/Graphics.hpp>

class Lifes : public sf::Drawable
{
public:
  Lifes(unsigned int lifeCount);
  
  /// Implementation of sf::Drawable interface
  void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
  
  /// Reduces the number of lifes. Return true if the number of lifes has reached 0
  bool decrement();
  
private:
  unsigned int _lifeCount;
  
  sf::Texture _texture;
  std::shared_ptr<sf::Sprite> _sprite;
};

#endif

#ifndef __SRC_OVERLAY_H__
#define __SRC_OVERLAY_H__

#include <memory>

#include <SFML/Graphics.hpp>

class Gameplay;

class Overlay : public sf::Drawable
{
public:
  Overlay(const std::shared_ptr<Gameplay> & gameplay);
  
  /// Implementation of sf::Drawable interface
  void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
  
  void onFailure();
  void clear();
  
private:
  std::shared_ptr<Gameplay> _gameplay;
  
  sf::Texture _lifeTexture;
  std::shared_ptr<sf::Sprite> _lifeSprite;
  
  sf::Texture _failMessage;
  std::vector<std::shared_ptr<sf::Sprite> > _overlaySprites;
};

#endif

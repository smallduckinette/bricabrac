#ifndef __CHAPITRE3_BALL_H__
#define __CHAPITRE3_BALL_H__

#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

#include "physics.h"

class Item;

class Ball : public sf::Sprite
{
public:
  Ball();

  /// Returns true if the ball is outside the boundaries (player has lost)
  bool update(sf::Time elapsed, std::list<std::shared_ptr<Item> > & world);
  
private:
  sf::Vector2f _position;
  sf::Vector2f _direction;
  float _velocity;
  
  sf::Texture _texture;
};

#endif

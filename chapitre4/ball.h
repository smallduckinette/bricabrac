#ifndef __CHAPITRE3_BALL_H__
#define __CHAPITRE3_BALL_H__

#include <memory>
#include <set>
#include <SFML/Graphics.hpp>

#include "physics.h"

class Item;

class Ball : public sf::Sprite
{
public:
  Ball();
  
  void update(sf::Time elapsed, std::set<std::shared_ptr<Item> > & world);
  
private:
  sf::Vector2f _position;
  sf::Vector2f _direction;
  float _velocity;
  
  sf::Texture _texture;
};

#endif

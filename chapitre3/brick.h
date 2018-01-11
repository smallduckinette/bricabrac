#ifndef __CHAPITRE2_BRICK_H__
#define __CHAPITRE2_BRICK_H__


#include <SFML/Graphics.hpp>

#include "item.h"
#include "physics.h"

class Brick : public sf::Sprite,
              public Item
{
public:
  Brick(const sf::Texture & texture, int x, int y);
  
  boost::optional<CollisionData> testCollision(const Disc & disc,
                                               const sf::Vector2f & direction,
                                               float velocity) const override;
  
  bool commitCollision() override;
  
  void draw(sf::RenderWindow * window) override;

private:
  int _x;
  int _y;
};

#endif

#ifndef __CHAPITRE3_PADDLE_H__
#define __CHAPITRE3_PADDLE_H__

#include <SFML/Graphics.hpp>
#include "item.h"

class Paddle : public sf::Sprite,
                public Item
{
public:
  Paddle();
  
  void move(int x);

  boost::optional<CollisionData> testCollision(const Disc & disc,
                                               const sf::Vector2f & direction,
                                               float velocity) const override;
  
  bool commitCollision() override;
  
  void draw(sf::RenderWindow * window) override;
  
private:
  sf::Texture _texture;
};

#endif

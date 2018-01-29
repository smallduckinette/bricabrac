#ifndef __CHAPITRE2_BRICK_H__
#define __CHAPITRE2_BRICK_H__

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "item.h"
#include "physics.h"

class Brick : public sf::Sprite,
              public Item
{
public:
  Brick(const sf::Texture & texture, int textureIndex, const std::shared_ptr<sf::Sound> & bing, int x, int y);
  
  boost::optional<CollisionData> testCollision(const Disc & disc,
                                               const sf::Vector2f & direction,
                                               float velocity) const override;
  
  bool commitCollision() override;
  
  void draw(sf::RenderWindow * window) override;
  
protected:
  void playSound();
  
private:
  int _x;
  int _y;
  std::shared_ptr<sf::Sound> _bing;
};

#endif

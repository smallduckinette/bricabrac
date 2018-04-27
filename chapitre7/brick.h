#ifndef __CHAPITRE2_BRICK_H__
#define __CHAPITRE2_BRICK_H__

#include <memory>

#include <SFML/Audio.hpp>

#include "item.h"
#include "physics.h"

class Brick : public Item
{
public:
  Brick(const sf::Texture & texture, int textureIndex, const std::shared_ptr<sf::Sound> & bing, int x, int y);
  
  boost::optional<CollisionData> testCollision(const Disc & disc,
                                               const sf::Vector2f & direction,
                                               float velocity) const override;
  
  bool commitCollision() override;
  
  bool requiredToWin() const override;
  
protected:
  void playSound();
  
private:
  std::shared_ptr<sf::Sound> _bing;
};

#endif

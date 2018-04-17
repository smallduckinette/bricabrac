#ifndef __CHAPITRE3_PADDLE_H__
#define __CHAPITRE3_PADDLE_H__

#include <SFML/Audio.hpp>
#include "item.h"

class Paddle : public Item
{
public:
  Paddle();
  
  void move(int x);

  boost::optional<CollisionData> testCollision(const Disc & disc,
                                               const sf::Vector2f & direction,
                                               float velocity) const override;
  
  bool commitCollision() override;
  
  bool requiredToWin() const override;
  
private:
  sf::Texture _texture;
  sf::SoundBuffer _soundBuffer;
  sf::Sound _sound;
};

#endif

#ifndef __CHAPITRE5_HARDBRICK_H__
#define __CHAPITRE5_HARDBRICK_H__

#include "brick.h"

class HardBrick : public Brick
{
public:
  HardBrick(const sf::Texture & texture, int textureIndex, const std::shared_ptr<sf::Sound> & bing, int x, int y);
  
  bool commitCollision() override;
  
private:
  int _hardness;
};

#endif

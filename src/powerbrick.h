#ifndef __CHAPITRE6_POWERBRICK_H__
#define __CHAPITRE6_POWERBRICK_H__

#include <memory>

#include <SFML/Graphics.hpp>

#include "physics.h"

/// The class that represents a power going down
class PowerBrick : public sf::Sprite
{
public:
  PowerBrick(const sf::Texture & texture, int textureIndex, int x, int y, float fallRate);
  
  /// Update the power brick. Returns true if the power is outside boundaries and
  /// needs to be removed
  bool update(sf::Time elapsed);
  
private:
  float _fallRate;
};

#endif

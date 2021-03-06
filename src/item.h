#ifndef __CHAPITRE2_ITEM_H__
#define __CHAPITRE2_ITEM_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <boost/optional.hpp>

#include "physics.h"

class Item : public sf::Sprite
{
public:
  /// Test collision with a disc of given radius, position, direction and speed
  virtual boost::optional<CollisionData> testCollision(const Disc & disc,
                                                       const sf::Vector2f & direction,
                                                       float velocity) const = 0;
  
  /// Indicate that the item was collided. Returns true if the item wants to be destroyed
  virtual bool commitCollision() = 0;
  
  /// Does the object have to be destroyed to win the level ?
  virtual bool requiredToWin() const = 0;
};

#endif

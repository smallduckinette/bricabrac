#ifndef __CHAPITRE7_MOVELISTENER_H__
#define __CHAPITRE7_MOVELISTENER_H__

#include <SFML/System/Vector2.hpp>

#include "entityid.h"

class MoveListener
{
public:
  virtual ~MoveListener() = default;
  virtual void onMove(EntityId entityId, const sf::Vector2f & position) = 0;
};

#endif

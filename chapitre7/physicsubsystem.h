#ifndef __CHAPITRE7_PHYSICSUBSYSTEM_H__
#define __CHAPITRE7_PHYSICSUBSYSTEM_H__

#include <map>

#include <SFML/System/Time.hpp>

#include "signal.h"
#include "physics.h"
#include "entityid.h"

class PhysicSubsystem
{
public:
  void addObstacle(EntityId entityId, const Rectangle & obstacle);
  void addDynamic(EntityId entityId, const Disc & disc);
  
  Signal<EntityId, EntityId> & onCollision();
  Signal<EntityId, sf::Vector2f> & onMove();

  void simulate(sf::Time elapsed);
  
private:
  struct Dynamic
  {
    Disc _shape;
    sf::Vector2f _direction;
    float _velocity;
    bool _static;
  };
  
  Signal<EntityId, EntityId> _collisionSignal;
  Signal<EntityId, sf::Vector2f> _moveSignal;
  
  std::map<EntityId, Rectangle> _obstacles;
  std::map<EntityId, Dynamic> _dynamics;
};

#endif

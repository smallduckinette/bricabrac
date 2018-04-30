#ifndef __CHAPITRE7_PHYSICSUBSYSTEM_H__
#define __CHAPITRE7_PHYSICSUBSYSTEM_H__

#include <map>
#include <memory>

#include <SFML/System/Time.hpp>

#include "signal.h"
#include "physics.h"
#include "entityid.h"
#include "movelistener.h"

class PhysicSubsystem
{
public:
  PhysicSubsystem() = default;
  PhysicSubsystem(const PhysicSubsystem &) = delete;
  PhysicSubsystem & operator=(const PhysicSubsystem &) = delete;
  
  void addObstacle(EntityId entityId, const std::shared_ptr<Rectangle> & obstacle, bool round = false);
  void addDynamic(EntityId entityId, const Disc & disc);
  
  void moveObstacle(EntityId entityId, const sf::Vector2f & position);
  void moveDynamic(EntityId entityId, const sf::Vector2f & position);
  
  bool isStatic(EntityId entityId) const;
  
  void setStatic(EntityId entityId);
  void setDynamic(EntityId entityId, const sf::Vector2f & direction);
  
  Signal<EntityId, EntityId> & onCollision();
  Signal<EntityId, sf::Vector2f> & onMove();

  void simulate(sf::Time elapsed);
    
private:
  struct Obstacle
  {
    std::shared_ptr<Rectangle> _shape;
    bool _round;
  };
  
  struct Dynamic
  {
    Disc _shape;
    sf::Vector2f _direction;
    float _velocity;
    bool _static;
  };
  
  Signal<EntityId, EntityId> _collisionSignal;
  Signal<EntityId, sf::Vector2f> _moveSignal;
  
  std::map<EntityId, Obstacle> _obstacles;
  std::map<EntityId, Dynamic> _dynamics;
};

#endif

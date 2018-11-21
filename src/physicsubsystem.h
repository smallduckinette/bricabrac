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
  
  void addObstacle(EntityId entityId,
                   const std::shared_ptr<Rectangle> & obstacle,
                   bool round,
                   int resistance,
                   bool catchBonus);
  void addDynamic(EntityId entityId, const Disc & disc);
  void addBonus(EntityId entityId,
                const OutsideRectangle & shape,
                float velocity);
  
  void moveObstacle(EntityId entityId, const sf::Vector2f & position);
  void moveDynamic(EntityId entityId, const sf::Vector2f & position);
  
  bool isStatic(EntityId entityId) const;
  
  void setStatic(EntityId entityId);
  void setDynamic(EntityId entityId, const sf::Vector2f & direction);
  
  Signal<EntityId, EntityId, sf::Vector2f> & onCollision();
  Signal<EntityId, sf::Vector2f> & onMove();
  Signal<EntityId> & onDestroy();
  
  void simulate(sf::Time elapsed);
  
private:
  struct Obstacle
  {
    std::shared_ptr<Rectangle> _shape;
    bool _round;
    int _resistance;
    bool _catchBonus;
  };
  
  struct Dynamic
  {
    Disc _shape;
    sf::Vector2f _direction;
    float _velocity;
    bool _static;
  };

  struct Bonus
  {
    OutsideRectangle _shape;
    float _velocity;
  };
  
  Signal<EntityId, EntityId, sf::Vector2f> _collisionSignal;
  Signal<EntityId, sf::Vector2f> _moveSignal;
  Signal<EntityId> _destroySignal;
  
  std::map<EntityId, Obstacle> _obstacles;
  std::map<EntityId, Dynamic> _dynamics;
  std::map<EntityId, Bonus> _bonus;
};

#endif

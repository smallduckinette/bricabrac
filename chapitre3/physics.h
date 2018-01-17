#ifndef __CHAPITRE2_PHYSICS_H__
#define __CHAPITRE2_PHYSICS_H__

#include "vector.h"
#include "collisiondata.h"

namespace physics
{
  CollisionDataOpt testHorizontalHit(float y,
                                     float minx, float maxx,
                                     const sf::Vector2f & position,
                                     const sf::Vector2f & direction,
                                     float velocity);
  CollisionDataOpt testVerticalHit(float x,
                                   float miny, float maxy,
                                   const sf::Vector2f & position,
                                   const sf::Vector2f & direction,
                                   float velocity);
  CollisionDataOpt testSphereHit(const sf::Vector2f & centre,
                                 float radius,
                                 const sf::Vector2f & position,
                                 const sf::Vector2f & direction,
                                 float velocity);
}

class Disc
{
public:
  Disc(const sf::Vector2f & position,
       float radius);
  
  sf::Vector2f _position;
  float _radius;
};

class Rectangle
{
public:
  Rectangle(const sf::Vector2f & m1,
            const sf::Vector2f & m2);
  
  CollisionDataOpt testHit(const Disc & disc,
                           const sf::Vector2f & direction,
                           float velocity) const;
  
private:  
  sf::Vector2f _min;
  sf::Vector2f _max;  
};

#endif

#ifndef __CHAPITRE2_PHYSICS_H__
#define __CHAPITRE2_PHYSICS_H__

#include <boost/optional.hpp>
#include <SFML/System/Vector2.hpp>

// Extend the SFML vectors with dot product operation
namespace sf
{
  template<typename T>
  T operator*(const Vector2<T> & left, const Vector2<T> & right)
  {
    return left.x * left.y + right.x * right.y;
  }
}

class CollisionData
{
public:
  CollisionData(const sf::Vector2f & position,
                const sf::Vector2f & direction,
                float residualVelocity);
  
  sf::Vector2f _position;
  sf::Vector2f _direction;
  float _residualVelocity;
};

bool operator<(const CollisionData & left, const CollisionData & right);

typedef boost::optional<CollisionData> CollisionDataOpt;

CollisionDataOpt operator^(const CollisionDataOpt & left, const CollisionDataOpt & right);

class Disc
{
public:
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
  CollisionDataOpt testHorizontalHit(float y,
                                     float minx, float maxx,
                                     const sf::Vector2f & position,
                                     const sf::Vector2f & direction,
                                     float velocity) const;
  CollisionDataOpt testVerticalHit(float x,
                                   float miny, float maxy,
                                   const sf::Vector2f & position,
                                   const sf::Vector2f & direction,
                                   float velocity) const;
  CollisionDataOpt testSphereHit(const sf::Vector2f & centre,
                                 float radius,
                                 const sf::Vector2f & position,
                                 const sf::Vector2f & direction,
                                 float velocity) const;
  
  sf::Vector2f _min;
  sf::Vector2f _max;  
};

#endif
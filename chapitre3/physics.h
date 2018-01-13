#ifndef __CHAPITRE2_PHYSICS_H__
#define __CHAPITRE2_PHYSICS_H__

#include <iostream>
#include <boost/optional.hpp>
#include <SFML/System/Vector2.hpp>

// Extend the SFML vectors with dot product operation
namespace sf
{
  template<typename T>
  T operator*(const Vector2<T> & left, const Vector2<T> & right)
  {
    return left.x * right.x + left.y * right.y;
  }
  
  template<typename T>
  std::ostream & operator<<(std::ostream & str, const Vector2<T> & v)
  {
    str << "(" << v.x << ", " << v.y << ")";
    return str;
  }
  
  template<typename T>
  bool close(const Vector2<T> & left, const Vector2<T> & right, T epsilon)
  {
    return (std::abs(left.x - right.x) < epsilon) && (std::abs(left.y - right.y) < epsilon);
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
bool operator==(const CollisionData & left, const CollisionData & right);
std::ostream & operator<<(std::ostream & str, const CollisionData & data);

typedef boost::optional<CollisionData> CollisionDataOpt;

CollisionDataOpt operator^(const CollisionDataOpt & left, const CollisionDataOpt & right);

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

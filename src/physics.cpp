#include "physics.h"

#include <cmath>

#include "collisiondata.h"


CollisionDataOpt physics::testHorizontalHit(float y,
                                            float minx, float maxx,
                                            const sf::Vector2f & position,
                                            const sf::Vector2f & direction,
                                            float velocity)
{
  float delta = (y - position.y) / direction.y;
  
  if(delta >= 0 && delta <= velocity)
  {
    sf::Vector2f newPosition = position + direction * delta;
    if(newPosition.x >= minx && newPosition.x <= maxx)
    {
       return CollisionData(newPosition,
                           sf::Vector2f(direction.x, -direction.y),
                           velocity - delta);
    }
  }
  return {};
}

CollisionDataOpt physics::testVerticalHit(float x,
                                          float miny, float maxy,
                                          const sf::Vector2f & position,
                                          const sf::Vector2f & direction,
                                          float velocity)
{
  float delta = (x - position.x) / direction.x;
  
  if(delta >= 0 && delta <= velocity)
  {
    sf::Vector2f newPosition = position + direction * delta;
    if(newPosition.y >= miny && newPosition.y <= maxy)
      return CollisionData(position + direction * delta,
                           sf::Vector2f(-direction.x, direction.y),
                           velocity - delta);
  }
  return {};
}

CollisionDataOpt physics::testSphereHit(const sf::Vector2f & centre,
                                        float radius,
                                        const sf::Vector2f & position,
                                        const sf::Vector2f & direction,
                                        float velocity)
{  
  sf::Vector2f pc = position - centre;
  float a = direction.x * direction.x + direction.y * direction.y;
  float b = 2 * (direction.x * pc.x + direction.y * pc.y);
  float c = pc.x * pc.x + pc.y * pc.y - radius * radius;

  float d = b * b - 4 * a * c;
  
  if(d >= 0)
  {
    float delta = (-b - std::sqrt(d)) / (2 * a);
    if(delta >= 0 && delta <= velocity)
    {
      // New position
      sf::Vector2f newPosition = position + direction * delta;
      
      // To calculate our new direction, we build a base from vector np - c
      sf::Vector2f newy = normalize(newPosition - centre);
      sf::Vector2f newx = sf::Vector2f(newy.y, -newy.x);
      
      // Project our direction vector in that base
      float projx = direction * newx;
      float projy = direction * newy;
      
      // Then build our new direction vector by doing a symetry on the new base x vector
      sf::Vector2f newDirection = projx * newx - projy * newy;
      
      return CollisionData(newPosition,
                           newDirection,
                           velocity - delta);
    }
  }
  return {};
}

Disc::Disc(const sf::Vector2f & position,
           float radius):
  _position(position),
  _radius(radius)
{
}

Rectangle::Rectangle(const sf::Vector2f & m1,
                     const sf::Vector2f & m2):
  _min(m1),
  _max(m2)
{
}

void Rectangle::setPosition(const sf::Vector2f & position)
{
  sf::Vector2f halfDiag = (_max - _min) * 0.5f;
  _min = position - halfDiag;
  _max = position + halfDiag;
}

sf::Vector2f Rectangle::getPosition() const
{
  return (_max - _min) * 0.5f + _min;
}

float Rectangle::getWidth() const
{
  return _max.x - _min.x;
}

float Rectangle::getHeight() const
{
  return _max.y - _min.y;
}

CollisionDataOpt OutsideRectangle::testHit(const Disc & disc,
                                           const sf::Vector2f & direction,
                                           float velocity) const
{
  CollisionDataOpt cd;
  if(direction.x != 0)
  {
    // Test against the right wall if we are going left,
    // or against the left wall if we are going right
    cd = cd ^ physics::testVerticalHit((direction.x < 0) ? (_max.x + disc._radius) : (_min.x - disc._radius),
                                       _min.y, _max.y,
                                       disc._position,
                                       direction,
                                       velocity);
    
    // Also test against the right spheres if we are going left, etc
    cd = cd ^ physics::testSphereHit((direction.x < 0) ? sf::Vector2f(_max.x, _min.y) : sf::Vector2f(_min.x, _min.y), 
                                     disc._radius,
                                     disc._position,
                                     direction,
                                     velocity);
    cd = cd ^ physics::testSphereHit((direction.x < 0) ? sf::Vector2f(_max.x, _max.y) : sf::Vector2f(_min.x, _max.y), 
                                     disc._radius,
                                     disc._position,
                                     direction,
                                     velocity);
  }
  if(direction.y != 0)
  {
    // Test against the top wall if we are going down,
    // or against the bottom wall if we are going up
    cd = cd ^ physics::testHorizontalHit((direction.y < 0) ? (_max.y + disc._radius) : (_min.y - disc._radius),
                                         _min.x, _max.x,
                                         disc._position,
                                         direction,
                                         velocity);
    
    // And same with spheres
    cd = cd ^ physics::testSphereHit((direction.y < 0) ? sf::Vector2f(_min.x, _max.y) : sf::Vector2f(_min.x, _min.y), 
                                     disc._radius,
                                     disc._position,
                                     direction,
                                     velocity);
    cd = cd ^ physics::testSphereHit((direction.y < 0) ? sf::Vector2f(_max.x, _max.y) : sf::Vector2f(_max.x, _min.y), 
                                     disc._radius,
                                     disc._position,
                                     direction,
                                     velocity);    
  }  
  
  return cd;
}

bool OutsideRectangle::testHit(const OutsideRectangle & rectangle) const
{
  return (rectangle._min.x <= _max.x && rectangle._max.x >= _min.x &&
          rectangle._min.y <= _max.y && rectangle._max.y >= _min.y);
}

CollisionDataOpt InsideRectangle::testHit(const Disc & disc,
                                          const sf::Vector2f & direction,
                                          float velocity) const
{
  CollisionDataOpt cd;
  if(direction.x != 0)
  {
    // Test against the left wall if we are going left,
    // or against the right wall if we are going right
    cd = cd ^ physics::testVerticalHit((direction.x < 0) ? (_min.x + disc._radius) : (_max.x - disc._radius),
                                       _min.y, _max.y,
                                       disc._position,
                                       direction,
                                       velocity);
  }
  if(direction.y != 0)
  {
    // Test against the top wall if we are going down,
    // or against the bottom wall if we are going up
    cd = cd ^ physics::testHorizontalHit((direction.y < 0) ? (_min.y + disc._radius) : (_max.y - disc._radius),
                                         _min.x, _max.x,
                                         disc._position,
                                         direction,
                                         velocity);
  }
  
  return cd;
}

bool InsideRectangle::testHit(const OutsideRectangle & ) const
{
  return false;
}

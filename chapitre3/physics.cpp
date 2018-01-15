#include "physics.h"
#include "collisiondata.h"

CollisionData::CollisionData(const sf::Vector2f & position,
                             const sf::Vector2f & direction,
                             float residualVelocity):
  _position(position),
  _direction(direction),
  _residualVelocity(residualVelocity)
{
}

bool operator<(const CollisionData & left, const CollisionData & right)
{
  return left._residualVelocity < right._residualVelocity;
}

CollisionDataOpt operator^(const CollisionDataOpt & left, const CollisionDataOpt & right)
{
  if(left && right)
  {
    return std::max(left, right);
  }
  else if(left)
  {
    return left;
  }
  else
    return right;
}

bool operator==(const CollisionData & left, const CollisionData & right)
{
  return
    sf::close(left._position, right._position, 0.01f) &&
    sf::close(left._direction, right._direction, 0.01f) &&
    (std::abs(left._residualVelocity - right._residualVelocity) < 0.01f);
}

std::ostream & operator<<(std::ostream & str, const CollisionData & data)
{
  str << data._position << ", " << data._direction << ", " << data._residualVelocity;
  return str;
}

sf::Vector2f normalize(const sf::Vector2f & v)
{
  float norm = std::sqrt(v.x * v.x + v.y * v.y);
  return sf::Vector2f(v.x / norm, v.y / norm);
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

CollisionDataOpt Rectangle::testHit(const Disc & disc,
                                    const sf::Vector2f & direction,
                                    float velocity) const
{
  CollisionDataOpt cd;
  if(direction.x != 0)
  {
    // Test against the right wall if we are going left,
    // or against the left wall if we are going right
    cd = cd ^ testVerticalHit((direction.x < 0) ? (_max.x + disc._radius) : (_min.x - disc._radius),
                              _min.y, _max.y,
                              disc._position,
                              direction,
                              velocity);
    
    // Also test against the right spheres if we are going left, etc
    cd = cd ^ testSphereHit((direction.x < 0) ? sf::Vector2f(_max.x, _min.y) : sf::Vector2f(_min.x, _min.y), 
                            disc._radius,
                            disc._position,
                            direction,
                            velocity);
    cd = cd ^ testSphereHit((direction.x < 0) ? sf::Vector2f(_max.x, _max.y) : sf::Vector2f(_min.x, _max.y), 
                            disc._radius,
                            disc._position,
                            direction,
                            velocity);
  }
  if(direction.y != 0)
  {
    // Test against the top wall if we are going down,
    // or against the bottom wall if we are going up
    cd = cd ^ testHorizontalHit((direction.y < 0) ? (_max.y + disc._radius) : (_min.y - disc._radius),
                                _min.x, _max.x,
                                disc._position,
                                direction,
                                velocity);
    
    // And same with spheres
    cd = cd ^ testSphereHit((direction.y < 0) ? sf::Vector2f(_min.x, _max.y) : sf::Vector2f(_min.x, _min.y), 
                            disc._radius,
                            disc._position,
                            direction,
                            velocity);
    cd = cd ^ testSphereHit((direction.y < 0) ? sf::Vector2f(_max.x, _max.y) : sf::Vector2f(_max.x, _min.y), 
                            disc._radius,
                            disc._position,
                            direction,
                            velocity);    
  }  
  
  return cd;
}

CollisionDataOpt Rectangle::testHorizontalHit(float y,
                                              float minx, float maxx,
                                              const sf::Vector2f & position,
                                              const sf::Vector2f & direction,
                                              float velocity) const
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

CollisionDataOpt Rectangle::testVerticalHit(float x,
                                            float miny, float maxy,
                                            const sf::Vector2f & position,
                                            const sf::Vector2f & direction,
                                            float velocity) const
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

CollisionDataOpt Rectangle::testSphereHit(const sf::Vector2f & centre,
                                          float radius,
                                          const sf::Vector2f & position,
                                          const sf::Vector2f & direction,
                                          float velocity) const
{  
  sf::Vector2f pc = position - centre;
  float a = direction.x * direction.x + direction.y * direction.y;
  float b = 2 * (direction.x * pc.x + direction.y * pc.y);
  float c = pc.x * pc.x + pc.y * pc.y - radius * radius;

  float d = b * b - 4 * a * c;
  
  if(d >= 0)
  {
    float delta = (-b - sqrt(d)) / (2 * a);
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

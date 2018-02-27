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

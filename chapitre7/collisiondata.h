#ifndef __CHAPITRE2_COLLISIONDATA_H__
#define __CHAPITRE2_COLLISIONDATA_H__

#include <boost/optional.hpp>
#include "vector.h"

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


#endif

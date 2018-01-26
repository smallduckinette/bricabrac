#include "frame.h"

#include "physics.h"

Frame::Frame(int x, int y):
  _x(x),
  _y(y)
{
}

boost::optional<CollisionData> Frame::testCollision(const Disc & disc,
                                                    const sf::Vector2f & direction,
                                                    float velocity) const
{
  CollisionDataOpt cd;
  if(direction.x < 0)
  {
    cd = cd ^ physics::testVerticalHit(disc._radius,
                                       0, _y,
                                       disc._position,
                                       direction,
                                       velocity);
  }
  else if(direction.x > 0)
  {
    cd = cd ^ physics::testVerticalHit(_x - disc._radius,
                                       0, _y,
                                       disc._position,
                                       direction,
                                       velocity);
  }
  if(direction.y < 0)
  {
    cd = cd ^ physics::testHorizontalHit(disc._radius,
                                         0, _x,
                                         disc._position,
                                         direction,
                                         velocity);
  }
  return cd;
}

bool Frame::commitCollision()
{
  return false;
}

void Frame::draw(sf::RenderWindow *)
{
  // Do nothing, the frame isn't displayed now
}

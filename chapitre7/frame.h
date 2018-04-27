#ifndef __CHAPITRE3_FRAME_H__
#define __CHAPITRE3_FRAME_H__

#include "item.h"


class Frame : public Item
{
public:
  Frame(int x, int y);
  
  boost::optional<CollisionData> testCollision(const Disc & disc,
                                               const sf::Vector2f & direction,
                                               float velocity) const override;
  
  bool commitCollision() override;
  
  bool requiredToWin() const override;
  
private:
  int _x;
  int _y;
};

#endif

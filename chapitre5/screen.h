#ifndef __CHAPITRE5_SCREEN_H__
#define __CHAPITRE5_SCREEN_H__

#include <list>
#include <memory>
#include <istream>

class Item;
class BrickFactory;

void buildScreen(const BrickFactory & brickFactory,
                 std::istream & str,
                 std::list<std::shared_ptr<Item> > & world);

#endif

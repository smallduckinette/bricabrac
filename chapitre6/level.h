#ifndef __CHAPITRE5_LEVEL_H__
#define __CHAPITRE5_LEVEL_H__

#include <list>
#include <memory>
#include <istream>

class Item;
class BrickFactory;

void buildLevel(const BrickFactory & brickFactory,
                std::istream & str,
                std::list<std::shared_ptr<Item> > & world);

#endif

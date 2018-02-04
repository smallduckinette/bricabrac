#include "level.h"

#include <sstream>
#include <algorithm>
#include <iterator>

#include "brickfactory.h"

void buildLevel(const BrickFactory & brickFactory,
                std::istream & str,
                std::list<std::shared_ptr<Item> > & world)
{
  int row = 0;
  std::string line;
  while(str.good())
  {
    std::getline(str, line, '\n');
    int col = 0;
    std::istringstream linestr(line);
    std::for_each(std::istream_iterator<int>(linestr),
                  std::istream_iterator<int>(),
                  [&](int brickType)
                  {
                    if(brickType > 0)
                    {
                      world.push_back(brickFactory.create(row, col, brickType));
                    }
                    ++col;
                  });
    ++row;
  }
}

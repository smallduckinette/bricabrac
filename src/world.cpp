#include "world.h"

#include "item.h"
#include "powerbrick.h"


void World::update(sf::Time elapsed)
{
  for(auto && power : _powers)
  {
    power->update(elapsed);
  }
}

void World::draw(sf::RenderTarget & target,
                 sf::RenderStates states) const
{
  for(auto && item : _items)
  {
    target.draw(*item, states);
  }
  for(auto && power : _powers)
  {
    target.draw(*power, states);
  }
}

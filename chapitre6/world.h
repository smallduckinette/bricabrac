#ifndef __CHAPITRE6_WORLD_H__
#define __CHAPITRE6_WORLD_H__

#include <list>
#include <memory>

#include <SFML/Graphics.hpp>

class Item;
class PowerBrick;

class World : public sf::Drawable
{
public:
  World() {}
  World(const World &) = delete;
  World & operator=(const World &) = delete;
  
  void draw(sf::RenderTarget & target,
            sf::RenderStates states) const override;
  
  std::list<std::shared_ptr<Item> > _items;
  std::list<std::shared_ptr<PowerBrick> > _powers;
};

#endif

#ifndef __CHAPITRE5_SCREEN_H__
#define __CHAPITRE5_SCREEN_H__

#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Event;

class Screen
{
public:
  virtual ~Screen() = default;
  
  virtual std::shared_ptr<Screen> onMouseMove(int x, int y);
  virtual std::shared_ptr<Screen> onFrame(sf::Time elapsed);
  virtual void draw(sf::RenderWindow & window);
};

#endif

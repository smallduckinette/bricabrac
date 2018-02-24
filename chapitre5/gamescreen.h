#ifndef __CHAPITRE5_GAMESCREEN_H__
#define __CHAPITRE5_GAMESCREEN_H__

#include "brickfactory.h"
#include "screen.h"

#include <list>

class Item;
class Ball;
class Paddle;

class GameScreen : public Screen
{
public:
  GameScreen(sf::RenderWindow * window,
             float initialVelocity,
             float maxVelocity,
             float acceleration);
  
  std::shared_ptr<Screen> onMouseMove(int x, int y) override;
  std::shared_ptr<Screen> onKey(const sf::Event::KeyEvent & key) override;
  std::shared_ptr<Screen> onFrame(sf::Time elapsed) override;
  void draw() override;
  
private:
  sf::RenderWindow * _window;
  
  BrickFactory _brickFactory;
  std::list<std::shared_ptr<Item> > _world;
  std::shared_ptr<Ball> _ball;
  std::shared_ptr<Paddle> _paddle;
  float _initialVelocity;
  float _maxVelocity;
  float _acceleration;
};

#endif

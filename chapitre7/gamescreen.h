#ifndef __CHAPITRE5_GAMESCREEN_H__
#define __CHAPITRE5_GAMESCREEN_H__

#include "brickfactory.h"
#include "screen.h"
#include "world.h"
#include "graphicsubsystem.h"


class Item;
class Ball;
class Paddle;
class Lifes;
class Gameplay;

class GameScreen : public Screen
{
public:
  GameScreen(sf::RenderWindow * window,
             float initialVelocity,
             float maxVelocity,
             float acceleration,
             const std::shared_ptr<Gameplay> & gameplay);
  
  std::shared_ptr<Screen> onMouseMove(int x, int y) override;
  std::shared_ptr<Screen> onMouseClick(sf::Mouse::Button, int x, int y);
  std::shared_ptr<Screen> onKey(const sf::Event::KeyEvent & key) override;
  std::shared_ptr<Screen> onFrame(sf::Time elapsed) override;
  void draw() override;
  
private:
  void makeLevel();
  
  sf::RenderWindow * _window;
  
  BrickFactory _brickFactory;
  World _world;
  std::shared_ptr<Ball> _ball;
  std::shared_ptr<Paddle> _paddle;
  std::shared_ptr<Lifes> _lifes;
  float _initialVelocity;
  float _maxVelocity;
  float _acceleration;
  std::shared_ptr<Gameplay> _gameplay;
  
  EntityIdGenerator _entityIdGenerator;
  
  GraphicSubsystem _graphicSubsystem;
};

#endif

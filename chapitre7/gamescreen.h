#ifndef __CHAPITRE5_GAMESCREEN_H__
#define __CHAPITRE5_GAMESCREEN_H__

#include "screen.h"
#include "world.h"
#include "graphicsubsystem.h"
#include "physicsubsystem.h"


class Item;
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
  
  World _world;
  std::shared_ptr<Lifes> _lifes;
  float _initialVelocity;
  float _maxVelocity;
  float _acceleration;
  std::shared_ptr<Gameplay> _gameplay;
  EntityIdGenerator _entityIdGenerator;
  EntityId _paddleId;
  EntityId _ballId;
  
  GraphicSubsystem _graphicSubsystem;
  PhysicSubsystem _physicSubsystem;
};

#endif

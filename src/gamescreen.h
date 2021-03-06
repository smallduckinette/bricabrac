#ifndef __CHAPITRE5_GAMESCREEN_H__
#define __CHAPITRE5_GAMESCREEN_H__

#include "screen.h"
#include "world.h"
#include "graphicsubsystem.h"
#include "physicsubsystem.h"
#include "soundsubsystem.h"
#include "overlay.h"

#include <boost/property_tree/ptree.hpp>

class Item;
class Gameplay;

class GameScreen : public Screen,
                   public MoveListener
{
public:
  GameScreen(sf::RenderWindow * window,
             float initialVelocity,
             float maxVelocity,
             float acceleration,
             const std::shared_ptr<Gameplay> & gameplay,
             const boost::property_tree::ptree & config);
  
  std::shared_ptr<Screen> onMouseMove(int x, int y) override;
  std::shared_ptr<Screen> onMouseClick(sf::Mouse::Button, int x, int y);
  std::shared_ptr<Screen> onKey(const sf::Event::KeyEvent & key) override;
  std::shared_ptr<Screen> onFrame(sf::Time elapsed) override;
  void draw() override;
  
private:
  void onMove(EntityId entityId, const sf::Vector2f & position) override;
  void onDestroy(EntityId entityId);
  
  void makeLevel();
  
  sf::RenderWindow * _window;
  
  World _world;
  Overlay _overlay;
  float _initialVelocity;
  float _maxVelocity;
  float _acceleration;
  std::shared_ptr<Gameplay> _gameplay;
  boost::property_tree::ptree _config;
  EntityIdGenerator _entityIdGenerator;
  EntityId _paddleId;
  EntityId _ballId;
  int _mouseX;

  enum Status
    {
      RUNNING,
      FAIL,
      SUCCESS,
      PAUSE
    } _status;
  sf::Time _pauseTime;
  
  GraphicSubsystem _graphicSubsystem;
  PhysicSubsystem _physicSubsystem;
  SoundSubsystem _soundSubsystem;
  
  std::set<EntityId> _entitiesToDelete;
};

#endif

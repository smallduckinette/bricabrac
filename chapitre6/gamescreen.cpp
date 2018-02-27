#include "gamescreen.h"

#include <fstream>

#include "paddle.h"
#include "ball.h"
#include "level.h"
#include "frame.h"
#include "titlescreen.h"

GameScreen::GameScreen(sf::RenderWindow * window,
                       float initialVelocity,
                       float maxVelocity,
                       float acceleration):
  _window(window),
  _ball(std::make_shared<Ball>(initialVelocity,
                               maxVelocity,
                               acceleration)),
  _paddle(std::make_shared<Paddle>()),
  _initialVelocity(initialVelocity),
  _maxVelocity(maxVelocity),
  _acceleration(acceleration)
{
  _window->setMouseCursorVisible(false);
  
  // Bricks
  std::ifstream level("../resources/screen1.txt");
  buildLevel(_brickFactory, level, _world);

  // Outside walls
  _world.push_back(std::make_shared<Frame>(800, 600));

  // Paddle
  _world.push_back(_paddle);
  
  //sf::Mouse::setPosition(sf::Vector2i(400, 560), window);
}

std::shared_ptr<Screen> GameScreen::onMouseMove(int x, int)
{
  _paddle->move(x);
  if(_ball->isSticky())
  {
    _ball->setPosition(_paddle->getPosition() - sf::Vector2f(0, 10));
  }
  return nullptr;
}

std::shared_ptr<Screen> GameScreen::onMouseClick(sf::Mouse::Button, int, int)
{
  _ball->setSticky(false);
  return nullptr;
}

std::shared_ptr<Screen> GameScreen::onKey(const sf::Event::KeyEvent & key)
{
  if(key.code == sf::Keyboard::Escape)
  {
    return std::make_shared<TitleScreen>(_window);
  }
  else return nullptr;  
}

std::shared_ptr<Screen> GameScreen::onFrame(sf::Time elapsed)
{
  if(_ball->update(elapsed, _world))
  {
    return std::make_shared<GameScreen>(_window, _initialVelocity, _maxVelocity, _acceleration);
  }
  else
  {
    return nullptr;
  }
}

void GameScreen::draw()
{
  _window->draw(*_ball);
  for(auto && item : _world)
  {
    item->draw(_window);
  }
}

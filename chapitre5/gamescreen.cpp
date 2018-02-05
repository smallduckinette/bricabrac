#include "gamescreen.h"

#include <fstream>

#include "paddle.h"
#include "ball.h"
#include "level.h"
#include "frame.h"

GameScreen::GameScreen():
  _ball(std::make_shared<Ball>()),
  _paddle(std::make_shared<Paddle>())
{
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
  return nullptr;
}

std::shared_ptr<Screen> GameScreen::onFrame(sf::Time elapsed)
{
  if(_ball->update(elapsed, _world))
  {
    return std::make_shared<GameScreen>();
  }
  else
  {
    return nullptr;
  }
}

void GameScreen::draw(sf::RenderWindow & window)
{
  window.draw(*_ball);
  for(auto && item : _world)
  {
    item->draw(&window);
  }
}

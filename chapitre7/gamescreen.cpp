#include "gamescreen.h"

#include <fstream>

#include "paddle.h"
#include "ball.h"
#include "level.h"
#include "lifes.h"
#include "frame.h"
#include "titlescreen.h"
#include "gameplay.h"
#include "spritedef.h"

GameScreen::GameScreen(sf::RenderWindow * window,
                       float initialVelocity,
                       float maxVelocity,
                       float acceleration,
                       const std::shared_ptr<Gameplay> & gameplay):
  _window(window),
  _ball(std::make_shared<Ball>(initialVelocity,
                               maxVelocity,
                               acceleration)),
  _paddle(std::make_shared<Paddle>()),
  _lifes(std::make_shared<Lifes>(gameplay)),
  _initialVelocity(initialVelocity),
  _maxVelocity(maxVelocity),
  _acceleration(acceleration),
  _gameplay(gameplay)
{
  _window->setMouseCursorVisible(false);
  
  _physicSubsystem.onMove().connect(&_graphicSubsystem, &GraphicSubsystem::onMove);
  
  //                                  std::bind(&GraphicSubsystem::onMove,
  //                                            &_graphicSubsystem,
  //                                            std::placeholders::_1,
  //                                            std::placeholders::_2));
  
  makeLevel();
  
  // Bricks
  //std::ifstream level(gameplay->getCurrentLevel().getLevelFilename().c_str());
  //if(!level.good())
  //  throw std::runtime_error("Cannot find level description file " + gameplay->getCurrentLevel().getLevelFilename());
  //buildLevel(_brickFactory, level, _world._items);
  
  // Outside walls
  _world._items.push_back(std::make_shared<Frame>(800, 600));
  
  // Paddle
  _world._items.push_back(_paddle);
  
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
  _physicSubsystem.simulate(elapsed);
  
  if(_ball->update(elapsed, _world._items))
  {
    // We got out of the screen, reduce the number of lives
    if(_gameplay->failure())
    {
      // We ran out of lifes, reset the game
      return std::make_shared<GameScreen>(_window, _initialVelocity, _maxVelocity, _acceleration, _gameplay);
    }
    else
    {
      // Reset ball position and carry on playing
      _ball->reset(_paddle->getPosition() - sf::Vector2f(0, 10));
      return nullptr;
    }
  }
  //else if(std::find_if(_world._items.begin(), _world._items.end(), [](auto && item) { return item->requiredToWin(); }) == _world._items.end())
  //{
  //  // Success! Go to the next stage
  //  _gameplay->success();
  //  
  //  return std::make_shared<GameScreen>(_window, _initialVelocity, _maxVelocity, _acceleration, _gameplay);
  //}
  else
  {
    return nullptr;
  }
}

void GameScreen::draw()
{
  _window->draw(*_ball);
  _window->draw(_world);
  _window->draw(*_lifes);
  
  _window->draw(_graphicSubsystem);
}

void GameScreen::makeLevel()
{
  std::ifstream level(_gameplay->getCurrentLevel().getLevelFilename().c_str());
  if(!level.good())
    throw std::runtime_error("Cannot find level description file " + _gameplay->getCurrentLevel().getLevelFilename());

  // Add bricks
  int row = 0;
  std::string line;
  while(level.good())
  {
    std::getline(level, line, '\n');
    int col = 0;
    std::istringstream linestr(line);
    std::for_each(std::istream_iterator<int>(linestr),
                  std::istream_iterator<int>(),
                  [&](int brickType)
                  {
                    if(brickType > 0)
                    {
                      EntityId entityId = _entityIdGenerator.generate();
                      sf::Vector2f position(col * 50, row * 30 + 50);
                      
                      _graphicSubsystem.add(entityId,
                                            SpriteDef("../resources/brick_sprite_sheet.png",
                                                      sf::IntRect(0, (brickType - 1) * 30, 50, 30)),
                                            position);
                      _physicSubsystem.addObstacle(entityId, Rectangle(position, position + sf::Vector2f(50, 30)));
                    }
                    ++col;
                  });
    ++row;
  }

  // Add ball
  EntityId ballId = _entityIdGenerator.generate();
  sf::Vector2f ballPosition(50, 50);
  _graphicSubsystem.add(ballId,
                        SpriteDef("../resources/bille.png",
                                  sf::IntRect(0, 0, 20, 20)),
                        ballPosition);
  _physicSubsystem.addDynamic(ballId, Disc(ballPosition, 10));
}

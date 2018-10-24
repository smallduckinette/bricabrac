#include "titlescreen.h"

#include <fstream>
#include <boost/property_tree/json_parser.hpp>

#include "gamescreen.h"
#include "gameplay.h"

TitleScreen::TitleScreen(sf::RenderWindow * window):
  GuiScreen(window)
{
  std::ifstream configFile("resources/config.json");
  boost::property_tree::json_parser::read_json(configFile, _config);
  
  _window->setMouseCursorVisible(true);
  
  addBackground("resources/title.png");
  
  _easy = addButton("resources/button.png", 150, 220);
  addButton("resources/easy.png", 150, 220);
  
  _medium = addButton("resources/button.png", 325, 220);
  addButton("resources/medium.png", 325, 220);
  
  _hard = addButton("resources/button.png", 500, 220);
  addButton("resources/hard.png", 500, 220);
  
  if(_music.openFromFile("resources/bossa.ogg"))
  {
    _music.play();
  }
}

std::shared_ptr<Screen> TitleScreen::onMouseClick(sf::Mouse::Button, int x, int y)
{
  if(hit(x, y, _easy))
  {
    return std::make_shared<GameScreen>(_window, 200, 300, 1, makeGameplay("resources/gameplay.json"), _config);
  }
  else if(hit(x, y, _medium))
  {
    return std::make_shared<GameScreen>(_window, 300, 600, 1, makeGameplay("resources/gameplay.json"), _config);
  }
  else if(hit(x, y, _hard))
  {
    return std::make_shared<GameScreen>(_window, 300, 800, 2, makeGameplay("resources/gameplay.json"), _config);
  }
  else
  {
    return nullptr;
  }
}

std::shared_ptr<Screen> TitleScreen::onKey(const sf::Event::KeyEvent & key)
{
  if(key.code == sf::Keyboard::Escape)
  {
    _window->close();
  }
  return nullptr;
}

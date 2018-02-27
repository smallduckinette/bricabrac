#include "titlescreen.h"
#include "gamescreen.h"

TitleScreen::TitleScreen(sf::RenderWindow * window):
  GuiScreen(window)
{
  _window->setMouseCursorVisible(true);
  
  addBackground("../resources/title.png");
  
  _easy = addButton("../resources/button.png", 150, 220);
  addButton("../resources/easy.png", 150, 220);
  
  _medium = addButton("../resources/button.png", 325, 220);
  addButton("../resources/medium.png", 325, 220);
  
  _hard = addButton("../resources/button.png", 500, 220);
  addButton("../resources/hard.png", 500, 220);
}

std::shared_ptr<Screen> TitleScreen::onMouseClick(sf::Mouse::Button, int x, int y)
{
  if(hit(x, y, _easy))
  {
    return std::make_shared<GameScreen>(_window, 200, 300, 1);
  }
  else if(hit(x, y, _medium))
  {
    return std::make_shared<GameScreen>(_window, 300, 600, 1);
  }
  else if(hit(x, y, _hard))
  {
    return std::make_shared<GameScreen>(_window, 300, 800, 2);
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

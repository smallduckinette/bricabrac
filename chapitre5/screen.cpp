#include "screen.h"


std::shared_ptr<Screen> Screen::onMouseClick(int, int)
{
  return nullptr;
}

std::shared_ptr<Screen> Screen::onMouseMove(int, int)
{
  return nullptr;
}

std::shared_ptr<Screen> Screen::onKey(const sf::Event::KeyEvent &)
{
  return nullptr;
}

std::shared_ptr<Screen> Screen::onFrame(sf::Time)
{
  return nullptr;
}

void Screen::draw()
{
}

#include "guiscreen.h"


GuiScreen::GuiScreen(sf::RenderWindow * window):
  _window(window)
{
}

void GuiScreen::draw()
{
  for(auto && item : _items)
  {
    _window->draw(*item);
  }
}

void GuiScreen::addBackground(const std::string & file)
{
  auto texture = std::make_shared<sf::Texture>();
  texture->loadFromFile(file);
  auto sprite = std::make_shared<sf::Sprite>(*texture);
  _textures.push_back(texture);
  _items.push_back(sprite);
}

size_t GuiScreen::addButton(const std::string & file, int x, int y)
{
  auto texture = std::make_shared<sf::Texture>();
  texture->loadFromFile(file);
  auto sprite = std::make_shared<sf::Sprite>(*texture);
  _textures.push_back(texture);
  _items.push_back(sprite);
  
  sprite->setPosition(sf::Vector2f(x, y));
  
  return _items.size() - 1;
}

bool GuiScreen::hit(int x, int y, size_t button) const
{
  auto sprite = _items.at(button);
  return(x >= sprite->getPosition().x &&
         y >= sprite->getPosition().y &&
         x <= sprite->getPosition().x + sprite->getTextureRect().width &&
         y <= sprite->getPosition().y + sprite->getTextureRect().height);
}

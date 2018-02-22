#include "guiscreen.h"




void GuiScreen::draw(sf::RenderWindow & window)
{
  for(auto && item : _items)
  {
    window.draw(*item);
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

void GuiScreen::addButton(const std::string & file, int x, int y)
{
  auto texture = std::make_shared<sf::Texture>();
  texture->loadFromFile(file);
  auto sprite = std::make_shared<sf::Sprite>(*texture);
  _textures.push_back(texture);
  _items.push_back(sprite);
  
  sprite->setPosition(sf::Vector2f(x, y));
}

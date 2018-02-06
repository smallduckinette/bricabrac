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

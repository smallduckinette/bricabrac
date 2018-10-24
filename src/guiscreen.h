#ifndef __CHAPITRE5_GUISCREEN_H__
#define __CHAPITRE5_GUISCREEN_H__

#include "screen.h"

class GuiScreen : public Screen
{
public:
  GuiScreen(sf::RenderWindow * window);
  
  void draw() override;
  
  void addBackground(const std::string & file);
  size_t addButton(const std::string & file, int x, int y);
  
  bool hit(int x, int y, size_t button) const;

protected:
  sf::RenderWindow * _window;
  
private:
  std::vector<std::shared_ptr<sf::Sprite> > _items;
  std::vector<std::shared_ptr<sf::Texture> > _textures;
};

#endif

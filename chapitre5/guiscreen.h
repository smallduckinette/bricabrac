#ifndef __CHAPITRE5_GUISCREEN_H__
#define __CHAPITRE5_GUISCREEN_H__

#include "screen.h"

class GuiScreen : public Screen
{
public:
  void draw(sf::RenderWindow & window) override;
  
  void addBackground(const std::string & file);
  
private:
  std::vector<std::shared_ptr<sf::Drawable> > _items;
  std::vector<std::shared_ptr<sf::Texture> > _textures;
};

#endif

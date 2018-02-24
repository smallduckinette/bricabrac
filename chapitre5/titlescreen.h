#ifndef __CHAPITRE5_TITLESCREEN_H__
#define __CHAPITRE5_TITLESCREEN_H__

#include "guiscreen.h"

class TitleScreen : public GuiScreen
{
public:
  TitleScreen(sf::RenderWindow * window);
  
  std::shared_ptr<Screen> onMouseClick(int x, int y) override;
  std::shared_ptr<Screen> onKey(const sf::Event::KeyEvent & key) override;

private:
  int _easy;
  int _medium;
  int _hard;
};

#endif

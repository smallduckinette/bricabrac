#ifndef __CHAPITRE5_TITLESCREEN_H__
#define __CHAPITRE5_TITLESCREEN_H__

#include "guiscreen.h"

class TitleScreen : public GuiScreen
{
public:
  TitleScreen();
  
  std::shared_ptr<Screen> onMouseClick(int x, int y) override;
};

#endif

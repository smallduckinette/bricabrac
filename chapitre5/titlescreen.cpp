#include "titlescreen.h"
#include "gamescreen.h"

TitleScreen::TitleScreen()
{
  addBackground("../resources/title.png");
}

std::shared_ptr<Screen> TitleScreen::onMouseClick(int, int)
{
  return std::make_shared<GameScreen>();
}

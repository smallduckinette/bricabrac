#include "titlescreen.h"
#include "gamescreen.h"

TitleScreen::TitleScreen()
{
  addBackground("../resources/title.png");
  
  addButton("../resources/button.png", 150, 220);
  addButton("../resources/easy.png", 150, 220);
  
  addButton("../resources/button.png", 325, 220);
  addButton("../resources/medium.png", 325, 220);
  
  addButton("../resources/button.png", 500, 220);
  addButton("../resources/hard.png", 500, 220);
}

std::shared_ptr<Screen> TitleScreen::onMouseClick(int, int)
{
  return std::make_shared<GameScreen>();
}

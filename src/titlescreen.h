#ifndef __CHAPITRE5_TITLESCREEN_H__
#define __CHAPITRE5_TITLESCREEN_H__

#include <boost/property_tree/ptree.hpp>
#include <SFML/Audio.hpp>

#include "guiscreen.h"

class TitleScreen : public GuiScreen
{
public:
  TitleScreen(sf::RenderWindow * window);
  
  std::shared_ptr<Screen> onMouseClick(sf::Mouse::Button, int x, int y) override;
  std::shared_ptr<Screen> onKey(const sf::Event::KeyEvent & key) override;

private:
  boost::property_tree::ptree _config;
  sf::Music _music;
  
  int _easy;
  int _medium;
  int _hard;
};

#endif

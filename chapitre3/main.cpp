#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "plateau.h"
#include "brick.h"

int main()
{
  try
  {
    sf::RenderWindow window(sf::VideoMode(800, 600), "BricABrac");
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);
    
    sf::Texture texture;
    if(!texture.loadFromFile("../resources/brique.png"))
      throw std::runtime_error("Cannot find brique.png");
    texture.setSmooth(true);
    
    Plateau plateau;
    std::vector<Brick> bricks;
    for(int x = 0; x < 16; ++x)
    {
      for(int y = 0; y < 8; y++)
      {
        bricks.push_back(Brick(texture, x * 50, y * 30 + 50));
      }
    }
    
    sf::Mouse::setPosition(sf::Vector2i(400, 560), window);
  
    while(window.isOpen())
    {
      sf::Event event;
      while(window.pollEvent(event))
      {
        if(event.type == sf::Event::Closed)
        {
          window.close();
        }
        else if(event.type == sf::Event::MouseMoved)
        {
          plateau.move(event.mouseMove.x);
        }
      }
    
      window.clear();
      window.draw(plateau);
      for(auto && brick : bricks)
      {
        window.draw(brick);
      }
      window.display();
    }
  }
  catch(const std::exception & e)
  {
    std::cout << e.what() << std::endl;
  }
  
  return 0;
}

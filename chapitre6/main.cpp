#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "titlescreen.h"

int main()
{
  try
  {
    sf::RenderWindow window(sf::VideoMode(800, 600), "BricABrac");
    window.setVerticalSyncEnabled(true);
    
    std::shared_ptr<Screen> currentScreen = std::make_shared<TitleScreen>(&window);
    
    sf::Clock clock;
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
          auto screen = currentScreen->onMouseMove(event.mouseMove.x,
                                                   event.mouseMove.y);
          if(screen)
            currentScreen = screen;
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
          auto screen = currentScreen->onMouseClick(event.mouseButton.button,
                                                    event.mouseButton.x,
                                                    event.mouseButton.y);
          
          if(screen)
            currentScreen = screen;
        }
        else if(event.type == sf::Event::KeyPressed)
        {
          auto screen = currentScreen->onKey(event.key);

          if(screen)
            currentScreen = screen;
        }
      }
      
      sf::Time elapsed = clock.restart();
      
      auto screen = currentScreen->onFrame(elapsed);
      if(screen)
        currentScreen = screen;
      
      window.clear();
      currentScreen->draw();
      window.display();
    }
  }
  catch(const std::exception & e)
  {
    std::cout << e.what() << std::endl;
  }
  
  return 0;
}

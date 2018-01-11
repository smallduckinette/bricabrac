#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "BricABrac");
  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(false);
  
  sf::RectangleShape shape(sf::Vector2f(60, 20));
  shape.setFillColor(sf::Color::Green);
  sf::Mouse::setPosition(sf::Vector2i(350, 560), window);
  shape.setPosition(320, 560);
  
  
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
        shape.setPosition(event.mouseMove.x - 30, 560);
      }
    }
    
    window.clear();
    window.draw(shape);
    window.display();
  }
  
  return 0;
}

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "paddle.h"
#include "brick.h"
#include "ball.h"
#include "frame.h"

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
    
    std::vector<std::shared_ptr<Item> > world;
    for(int x = 0; x < 16; ++x)
    {
      for(int y = 0; y < 8; y++)
      {
        world.push_back(std::make_shared<Brick>(texture, x * 50, y * 30 + 50));
      }
    }
    
    world.push_back(std::make_shared<Frame>(800, 600));
    
    auto paddle = std::make_shared<Paddle>();
    world.push_back(paddle);
    
    Ball ball;
    
    sf::Mouse::setPosition(sf::Vector2i(400, 560), window);

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
          paddle->move(event.mouseMove.x);
        }
      }
      
      sf::Time elapsed = clock.restart();
      ball.update(elapsed, world);
      
      window.clear();
      window.draw(ball);
      for(auto && item : world)
      {
        item->draw(&window);
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

#include <SFML/Graphics.hpp>


class Plateau : public sf::Sprite
{
public:
  Plateau();
  
  void move(int x);
  
private:
  sf::Texture _texture;
};

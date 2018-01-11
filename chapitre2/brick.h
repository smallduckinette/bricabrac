#include <SFML/Graphics.hpp>


class Brick : public sf::Sprite
{
public:
  Brick(const sf::Texture & texture, int x, int y);
};

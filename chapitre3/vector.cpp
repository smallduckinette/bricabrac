#include "vector.h"

#include <cmath>

sf::Vector2f normalize(const sf::Vector2f & v)
{
  float norm = std::sqrt(v.x * v.x + v.y * v.y);
  return sf::Vector2f(v.x / norm, v.y / norm);
}

#include "vector.h"

#include <cmath>

sf::Vector2f sf::normalize(const sf::Vector2f & v)
{
  float n = norm(v);
  return sf::Vector2f(v.x / n, v.y / n);
}

float sf::norm(const sf::Vector2f & v)
{
  return std::sqrt(v.x * v.x + v.y * v.y);
}

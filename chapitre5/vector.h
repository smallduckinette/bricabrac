#ifndef __CHAPITRE3_VECTOR_H__
#define __CHAPITRE3_VECTOR_H__

#include <iostream>
#include <SFML/System/Vector2.hpp>

// Extend the SFML vectors with dot product operation
namespace sf
{
  template<typename T>
  T operator*(const Vector2<T> & left, const Vector2<T> & right)
  {
    return left.x * right.x + left.y * right.y;
  }
  
  template<typename T>
  std::ostream & operator<<(std::ostream & str, const Vector2<T> & v)
  {
    str << "(" << v.x << ", " << v.y << ")";
    return str;
  }
  
  template<typename T>
  bool close(const Vector2<T> & left, const Vector2<T> & right, T epsilon)
  {
    return (std::abs(left.x - right.x) < epsilon) && (std::abs(left.y - right.y) < epsilon);
  }
}

sf::Vector2f normalize(const sf::Vector2f & v);

#endif

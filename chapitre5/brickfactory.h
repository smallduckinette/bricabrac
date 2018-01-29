#ifndef __CHAPITRE5_BRICKFACTORY_H__
#define __CHAPITRE5_BRICKFACTORY_H__

#include <memory>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Item;

class BrickFactory
{
public:
  BrickFactory();
  BrickFactory(const BrickFactory &) = delete;
  BrickFactory & operator=(const BrickFactory &) = delete;
  
  std::shared_ptr<Item> create(int row, int col, int brickType) const;
  
private:
  sf::Texture _texture;
  sf::SoundBuffer _bingBuffer;
  std::shared_ptr<sf::Sound> _bing;
};

#endif

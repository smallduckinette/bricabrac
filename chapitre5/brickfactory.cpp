#include "brickfactory.h"

#include "brick.h"

BrickFactory::BrickFactory()
{
  if(!_texture.loadFromFile("../resources/brique.png"))
    throw std::runtime_error("Cannot find brique.png");
  _texture.setSmooth(true);
  
  if(!_bingBuffer.loadFromFile("../resources/bing.flac"))
    throw std::runtime_error("Cannot find bing.flac");
  _bing = std::make_shared<sf::Sound>(_bingBuffer);
}

std::shared_ptr<Item> BrickFactory::create(int row, int col) const
{
  return std::make_shared<Brick>(_texture, _bing, col * 50, row * 30 + 50);
}

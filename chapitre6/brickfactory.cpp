#include "brickfactory.h"

#include "brick.h"
#include "hardbrick.h"

BrickFactory::BrickFactory()
{
  if(!_texture.loadFromFile("../resources/brick_sprite_sheet.png"))
    throw std::runtime_error("Cannot find brick_sprite_sheet.png");
  _texture.setSmooth(true);
  
  if(!_bingBuffer.loadFromFile("../resources/bing.flac"))
    throw std::runtime_error("Cannot find bing.flac");
  _bing = std::make_shared<sf::Sound>(_bingBuffer);
}

std::shared_ptr<Item> BrickFactory::create(int row, int col, int brickType) const
{
  if(brickType == 5)
  {
    return std::make_shared<HardBrick>(_texture, brickType, _bing, col * 50, row * 30 + 50);
  }
  else
  {
    return std::make_shared<Brick>(_texture, brickType, _bing, col * 50, row * 30 + 50);
  }
}

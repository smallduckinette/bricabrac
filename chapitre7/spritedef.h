#ifndef __CHAPITRE7_SPRITEDEF_H__
#define __CHAPITRE7_SPRITEDEF_H__

class SpriteDef
{
public:
  SpriteDef(const std::string & textureFile,
            const sf::IntRect & textureRect,
            const sf::Vector2f & origin = sf::Vector2f(0, 0)):
    _textureFile(textureFile),
    _textureRect(textureRect),
    _origin(origin)
  {
  }
  
  std::string _textureFile;
  sf::IntRect _textureRect;
  sf::Vector2f _origin;
};

#endif

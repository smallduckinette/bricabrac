#ifndef __CHAPITRE7_SPRITEDEF_H__
#define __CHAPITRE7_SPRITEDEF_H__

class SpriteDef
{
public:
  SpriteDef(const std::string & textureFile,
            const sf::IntRect & textureRect):
    _textureFile(textureFile),
    _textureRect(textureRect)
  {
  }
  
  std::string _textureFile;
  sf::IntRect _textureRect;
};

#endif

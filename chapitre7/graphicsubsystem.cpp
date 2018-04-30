#include "graphicsubsystem.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "spritedef.h"


void GraphicSubsystem::add(EntityId entityId,
                           const SpriteDef & spriteDef,
                           const sf::Vector2f & position)
{
  // Create the texture if not already there
  auto result = _textures.insert({spriteDef._textureFile, nullptr});
  if(result.second)
  {
    result.first->second = std::make_shared<sf::Texture>();
    result.first->second->loadFromFile(spriteDef._textureFile);
  }
  
  sf::Sprite sprite(*result.first->second);
  sprite.setTextureRect(spriteDef._textureRect);
  sprite.setPosition(position);
  sprite.setOrigin(spriteDef._origin);
  
  _sprites.insert({entityId, sprite});
}

void GraphicSubsystem::draw(sf::RenderTarget & target,
                            sf::RenderStates states) const
{
  for(auto && sprite : _sprites)
  {
    target.draw(sprite.second, states);
  }
}

void GraphicSubsystem::onMove(EntityId entityId, const sf::Vector2f & position)
{
  auto it = _sprites.find(entityId);
  if(it != _sprites.end())
    it->second.setPosition(position);
}

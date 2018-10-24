#ifndef __CHAPITRE7_GRAPHICSUBSYSTEM_H__
#define __CHAPITRE7_GRAPHICSUBSYSTEM_H__

#include <map>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "entityid.h"
#include "movelistener.h"

class SpriteDef;

class GraphicSubsystem : public sf::Drawable,
                         public MoveListener
{
public:
  GraphicSubsystem() = default;
  GraphicSubsystem(const GraphicSubsystem &) = delete;
  GraphicSubsystem & operator=(const GraphicSubsystem &) = delete;

  void add(EntityId entityId,
           const SpriteDef & spriteDef,
           const sf::Vector2f & position);
  
  /// Implementation of the sf::Drawable interface
  void draw(sf::RenderTarget & target,
            sf::RenderStates states) const override;
  
  /// Implementation of the MoveListener interface
  void onMove(EntityId entityId, const sf::Vector2f & position) override;

  /// Destruction of an entity
  void onDestroy(EntityId entityId);
  
private:
  std::map<EntityId, sf::Sprite> _sprites;
  std::map<std::string, std::shared_ptr<sf::Texture> > _textures;
};

#endif

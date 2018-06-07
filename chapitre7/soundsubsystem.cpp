#include "soundsubsystem.h"


void SoundSubsystem::addEntity(EntityId entity, Material material)
{
  _entityMaterials.insert({entity, material});
}

void SoundSubsystem::onCollision(EntityId entity1, EntityId entity2, const sf::Vector2f & position)
{
  auto it1 = _entityMaterials.find(entity1);
  auto it2 = _entityMaterials.find(entity2);
  if(it1 != _entityMaterials.end() && it2 != _entityMaterials.end())
  {
    auto materialPair = std::make_pair(std::min(it1->second, it2->second), std::max(it1->second, it2->second));
    auto it_mp = _sounds.find(materialPair);
    if(it_mp != _sounds.end())
    {
      it_mp->second.setPosition((position.x - 400.0) / 400, 0, 0.1);
      it_mp->second.play();
    }
  }
}

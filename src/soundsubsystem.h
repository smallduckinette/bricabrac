#ifndef __CHAPITRE7_SOUNDSUBSYSTEM_H__
#define __CHAPITRE7_SOUNDSUBSYSTEM_H__

#include <map>
#include <boost/property_tree/ptree.hpp>

#include <SFML/Audio.hpp>

#include "entityid.h"

class SoundSubsystem
{
public:
  SoundSubsystem(const boost::property_tree::ptree & config);
  SoundSubsystem(const SoundSubsystem &) = delete;
  SoundSubsystem & operator=(const SoundSubsystem &) = delete;
  
  enum Material
    {
      Ball,
      Brick,
      Paddle,
      Wall
    };
  
  void add(EntityId entity, Material material);
  
  void onCollision(EntityId entity1, EntityId entity2, const sf::Vector2f & position);
  
  void onDestroy(EntityId entityId);
  
private:
  Material parseMaterial(const std::string & value) const;
  
  // Each material pair makes a particular sound (like, metal on wood). By convention,
  // the first material is the lowest.
  std::vector<std::shared_ptr<sf::SoundBuffer> > _soundBuffers;
  std::map<std::pair<Material, Material>, sf::Sound> _sounds;
  
  // Each entity is made of a certain material
  std::map<EntityId, Material> _entityMaterials;
};

#endif

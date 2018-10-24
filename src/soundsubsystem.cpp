#include "soundsubsystem.h"

#include <iostream>

SoundSubsystem::SoundSubsystem(const boost::property_tree::ptree & config)
{
  std::map<std::string, std::vector<std::pair<Material, Material> > > soundFiles;
  for(auto && s : config)
  {
    Material material1 = parseMaterial(s.second.get<std::string>("material1"));
    Material material2 = parseMaterial(s.second.get<std::string>("material2"));
    auto && sound = s.second.get<std::string>("sound");
    soundFiles[sound].push_back({std::min(material1, material2), std::max(material1, material2)});
  }
  
  for(auto && soundFile : soundFiles)
  {
    _soundBuffers.push_back(std::make_shared<sf::SoundBuffer>());
    _soundBuffers.back()->loadFromFile(soundFile.first);
    for(auto && mats : soundFile.second)
    {
      _sounds.insert({mats, sf::Sound(*_soundBuffers.back())});
    }
  }

  std::cout << "Loaded " << _sounds.size() << " sounds" << std::endl;
}

void SoundSubsystem::add(EntityId entity, Material material)
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

void SoundSubsystem::onDestroy(EntityId entityId)
{
  _entityMaterials.erase(entityId);
}

SoundSubsystem::Material SoundSubsystem::parseMaterial(const std::string & value) const
{
  if(value == "Ball")
    return Ball;
  else if(value == "Brick")
    return Brick;
  else if(value == "Paddle")
    return Paddle;
  else if(value == "Wall")
    return Wall;
  else
    throw std::runtime_error("Cannot parse material, value unknown: " + value);
}

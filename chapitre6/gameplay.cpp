#include "gameplay.h"


Gameplay::Gameplay(const boost::property_tree::ptree & ptree)
{
  for(auto && t : ptree.get_child("levels"))
  {
    _levels.push_back(std::make_shared<LevelDescription>(t.second));
  }
}

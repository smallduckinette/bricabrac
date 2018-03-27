#include "gameplay.h"


Gameplay::Gameplay(const boost::property_tree::ptree & ptree)
{
  for(auto && t : ptree)
  {
    _levels.push_back(std::make_shared<LevelDescription>(t.second));
  }
}

Gameplay::Gameplay(const Levels & levels):
  _levels(levels)
{
}

void Gameplay::save(boost::property_tree::ptree & ptree) const
{
  for(auto && level : _levels)
  {
    boost::property_tree::ptree subtree;
    level->save(subtree);
    ptree.add_child("levels", subtree);
  }
}

bool Gameplay::operator==(const Gameplay & other) const
{
  if(_levels.size() != other._levels.size())
    return false;

  auto it = _levels.begin();
  auto end = _levels.end();
  auto it2 = other._levels.begin();
  for(; it != end; ++it, ++it2)
  {
    if(!(**it == **it2))
      return false;
  }
  return true;
}

std::ostream & operator<<(std::ostream & str, const Gameplay & gameplay)
{
  str << "{";
  bool first = true;
  for(auto && level : gameplay._levels)
  {
    if(!first)
      str << ", ";
    first = false;
    str << *level;
  }
  str << "}";
  return str;
}

#include "gameplay.h"

#include <fstream>
#include <stdexcept>

#include <boost/property_tree/json_parser.hpp>

Gameplay::Gameplay(const boost::property_tree::ptree & ptree):
  _lives(ptree.get<unsigned int>("lives"))
{ 
  for(auto && t : ptree)
  {
    if(t.first == "levels")
      _levels.push_back(std::make_shared<LevelDescription>(t.second));
  }
  if(_levels.empty())
    throw std::runtime_error("No gameplay data");
  
  _currentLevel = _levels.begin();
}

Gameplay::Gameplay(int lives, const Levels & levels):
  _lives(lives),
  _levels(levels)
{
  if(_levels.empty())
    throw std::runtime_error("No gameplay data");
  
  _currentLevel = _levels.begin();
}

void Gameplay::save(boost::property_tree::ptree & ptree) const
{
  ptree.put("lives", _lives);
  
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

unsigned int Gameplay::getLives() const
{
  return _lives;
}

const LevelDescription & Gameplay::getCurrentLevel() const
{
  return **_currentLevel;
}

void Gameplay::success()
{
  ++_currentLevel;
}

bool Gameplay::failure()
{
  if(_lives == 0)
  {
    return true;
  }
  else
  {
    --_lives;
    return false;
  }
}

std::shared_ptr<Gameplay> makeGameplay(const std::string & settings)
{
  std::ifstream data(settings);
  boost::property_tree::ptree tree;
  boost::property_tree::json_parser::read_json(data, tree);
  
  return std::make_shared<Gameplay>(tree);
}

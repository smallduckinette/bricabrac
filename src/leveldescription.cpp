#include "leveldescription.h"


LevelDescription::LevelDescription(const boost::property_tree::ptree & ptree):
  _levelFilename(ptree.get<std::string>("file"))
{
}

LevelDescription::LevelDescription(const std::string & levelFilename):
  _levelFilename(levelFilename)
{
}

void LevelDescription::save(boost::property_tree::ptree & ptree) const
{
  ptree.add("file", _levelFilename);
}

std::string LevelDescription::getLevelFilename() const  
{
  return _levelFilename;
}

bool LevelDescription::operator==(const LevelDescription & other) const
{
  return _levelFilename == other._levelFilename;
}

std::ostream & operator<<(std::ostream & str, const LevelDescription & levelDescription)
{
  str << "{" << levelDescription._levelFilename << "}";
  return str;
}

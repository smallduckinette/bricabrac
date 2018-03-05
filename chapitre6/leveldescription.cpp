#include "leveldescription.h"


LevelDescription::LevelDescription(const boost::property_tree::ptree & ptree):
  _levelFilename(ptree.get<std::string>("file"))
{
}

std::string LevelDescription::getLevelFilename() const  
{
  return _levelFilename;
}

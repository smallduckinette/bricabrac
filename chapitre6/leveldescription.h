#ifndef __CHAPITRE6_LEVELDESCRIPTION_H__
#define __CHAPITRE6_LEVELDESCRIPTION_H__

#include <boost/property_tree/ptree.hpp>

class LevelDescription
{
public:
  LevelDescription(const boost::property_tree::ptree & ptree);
  
  std::string getLevelFilename() const;
  
private:
  std::string _levelFilename;
};

#endif

#ifndef __CHAPITRE6_GAMEPLAY_H__
#define __CHAPITRE6_GAMEPLAY_H__

#include <boost/property_tree/ptree.hpp>

#include "leveldescription.h"

class Gameplay
{
public:
  Gameplay(const boost::property_tree::ptree & ptree);

private:
  typedef std::vector<std::shared_ptr<const LevelDescription> > Levels;
  Levels _levels;
  Levels::const_iterator _currentLevel;
};

#endif

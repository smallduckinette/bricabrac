#ifndef __CHAPITRE6_GAMEPLAY_H__
#define __CHAPITRE6_GAMEPLAY_H__

#include <boost/property_tree/ptree.hpp>

#include "leveldescription.h"

class Gameplay
{
public:
  typedef std::vector<std::shared_ptr<const LevelDescription> > Levels;

  Gameplay(const boost::property_tree::ptree & ptree);
  Gameplay(const Levels & levels);
  
  void save(boost::property_tree::ptree & ptree) const;
  
  bool operator==(const Gameplay & other) const;
  
  friend std::ostream & operator<<(std::ostream & str, const Gameplay & gameplay);
  
private:
  Levels _levels;
  Levels::const_iterator _currentLevel;
};

#endif

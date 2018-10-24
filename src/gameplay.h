#ifndef __CHAPITRE6_GAMEPLAY_H__
#define __CHAPITRE6_GAMEPLAY_H__

#include <boost/property_tree/ptree.hpp>

#include "leveldescription.h"

class Gameplay
{
public:
  typedef std::vector<std::shared_ptr<const LevelDescription> > Levels;
  
  Gameplay(const boost::property_tree::ptree & ptree);
  Gameplay(int lives, const Levels & levels);
  
  Gameplay(const Gameplay &) = delete;
  Gameplay & operator=(const Gameplay &) = delete;
  
  void save(boost::property_tree::ptree & ptree) const;
  
  bool operator==(const Gameplay & other) const;
  
  friend std::ostream & operator<<(std::ostream & str, const Gameplay & gameplay);
  
  /// Return the current number of lives
  unsigned int getLives() const;
  
  /// Return the current level description
  const LevelDescription & getCurrentLevel() const;
  
  /// Success - User will get to the next level
  void success();
  
  /// Failure - Decrement the number of lives, returning true if we reached zero
  bool failure();
  
private:
  unsigned int _lives;
  Levels _levels;
  Levels::const_iterator _currentLevel;
};

std::shared_ptr<Gameplay> makeGameplay(const std::string & settings);

#endif

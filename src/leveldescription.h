#ifndef __CHAPITRE6_LEVELDESCRIPTION_H__
#define __CHAPITRE6_LEVELDESCRIPTION_H__

#include <boost/property_tree/ptree.hpp>

class LevelDescription
{
public:
  LevelDescription(const boost::property_tree::ptree & ptree);
  LevelDescription(const std::string & levelFilename);

  LevelDescription(const LevelDescription &) = delete;
  LevelDescription & operator=(const LevelDescription &) = delete;
  
  void save(boost::property_tree::ptree & ptree) const;
  
  std::string getLevelFilename() const;
  
  bool operator==(const LevelDescription & other) const;
  
  friend std::ostream & operator<<(std::ostream & str, const LevelDescription & levelDescription);
  
private:
  std::string _levelFilename;
};

#endif

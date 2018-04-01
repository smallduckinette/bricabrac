#include <boost/test/unit_test.hpp>

#include <sstream>
#include <boost/property_tree/json_parser.hpp>

#include "gameplay.h"

const char * fileContents =
  "{\n"
  "    \"lives\": \"3\",\n"
  "    \"levels\": {\n"
  "        \"file\": \"level1.txt\"\n"
  "    },\n"
  "    \"levels\": {\n"
  "        \"file\": \"level2.txt\"\n"
  "    }\n"
  "}\n";

std::shared_ptr<Gameplay> makeGameplay()
{
  return std::make_shared<Gameplay>
    (
     3,
     Gameplay::Levels
    {
      std::make_shared<LevelDescription>("level1.txt"),
        std::make_shared<LevelDescription>("level2.txt")
        }
     );
}

BOOST_AUTO_TEST_CASE(testSaveGameplay)
{
  auto gameplay = makeGameplay();
  
  boost::property_tree::ptree tree;
  gameplay->save(tree);
  std::ostringstream data;
  boost::property_tree::json_parser::write_json(data, tree);
  BOOST_CHECK_EQUAL(fileContents, data.str());
}

BOOST_AUTO_TEST_CASE(testLoadGameplay)
{
  std::istringstream data(fileContents);
  boost::property_tree::ptree tree;
  boost::property_tree::json_parser::read_json(data, tree);
  
  Gameplay gameplay(tree);
  auto expected = makeGameplay();
  BOOST_CHECK_EQUAL(*expected, gameplay);
}

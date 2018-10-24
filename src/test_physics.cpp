#include <boost/test/unit_test.hpp>

#include <boost/optional/optional_io.hpp>
#include "physics.h"

BOOST_AUTO_TEST_SUITE(Physics)

BOOST_AUTO_TEST_CASE(testRectangleCollisionsFromTop)
{
  OutsideRectangle r(sf::Vector2f(0, 0), sf::Vector2f(5, 3));
  
  // Hit straight down
  CollisionDataOpt c1 = r.testHit(Disc(sf::Vector2f(2, 6), 1),
                                  sf::Vector2f(0, -1),
                                  2);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(2, 4),
                                  sf::Vector2f(0, 1),
                                  0),
                    c1);
  
  // Hit down from angle
  CollisionDataOpt c2 = r.testHit(Disc(sf::Vector2f(4, 5), 1),
                                  sf::Vector2f(-1, -1),
                                  4);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(3, 4),
                                  sf::Vector2f(-1, 1),
                                  3),
                    c2);  
}

BOOST_AUTO_TEST_CASE(testRectangleCollisionsFromBottom)
{
  OutsideRectangle r(sf::Vector2f(0, 0), sf::Vector2f(5, 3));
  
  // Hit straight up
  CollisionDataOpt c1 = r.testHit(Disc(sf::Vector2f(2, -2), 1),
                                  sf::Vector2f(0, 1),
                                  3);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(2, -1),
                                  sf::Vector2f(0, -1),
                                  2),
                    c1);

  // Hit up at an angle
  CollisionDataOpt c2 = r.testHit(Disc(sf::Vector2f(2, -3), 1),
                                  sf::Vector2f(1, 2),
                                  1);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(3, -1),
                                  sf::Vector2f(1, -2),
                                  0),
                    c2);

  // Hit up at an angle  
}

BOOST_AUTO_TEST_CASE(testRectangleCollisionsCorners)
{
  OutsideRectangle r(sf::Vector2f(0, 0), sf::Vector2f(5, 3));
  
  // Hit from bottom left toward top right
  CollisionDataOpt c1 = r.testHit(Disc(sf::Vector2f(-2, -2), 1),
                                  sf::Vector2f(1, 1),
                                  3);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(-0.707, -0.707),
                                  sf::Vector2f(-1, -1),
                                  1.707),
                    c1);  

  // Hit from top left toward bottom right
  CollisionDataOpt c2 = r.testHit(Disc(sf::Vector2f(-2, 5), 1),
                                  sf::Vector2f(1, -1),
                                  3);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(-0.707, 3.707),
                                  sf::Vector2f(-1, 1),
                                  1.707),
                    c2);
  
  // Hit from bottom right toward top left
  CollisionDataOpt c3 = r.testHit(Disc(sf::Vector2f(7, -2), 1),
                                  sf::Vector2f(-1, 1),
                                  3);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(5.707, -0.707),
                                  sf::Vector2f(1, -1),
                                  1.707),
                    c3);  
  
  // Hit from top right toward bottom left
  CollisionDataOpt c4 = r.testHit(Disc(sf::Vector2f(7, 5), 1),
                                  sf::Vector2f(-1, -1),
                                  3);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(5.707, 3.707),
                                  sf::Vector2f(1, 1),
                                  1.707),
                    c4);  
  
}

BOOST_AUTO_TEST_CASE(testRectangleCollisionsComplexCorners)
{
  OutsideRectangle r(sf::Vector2f(0, 0), sf::Vector2f(5, 3));

  // We're going stright left, and are located slightly lower than the rectangle
  CollisionDataOpt c1 = r.testHit(Disc(sf::Vector2f(7, -0.5), 1),
                                  sf::Vector2f(-1, 0),
                                  3);
  
  BOOST_CHECK_EQUAL(CollisionData(sf::Vector2f(5.866, -0.5),
                                  sf::Vector2f(0.5, -0.866025),
                                  1.866),
                    c1);    
}

BOOST_AUTO_TEST_SUITE_END()

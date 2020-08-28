#include "catch.hpp"
#include "list.h"
#include <random>
#include <iostream>

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE( "Create an empty list" ) {
  List l{};

  REQUIRE( l.is_empty() == true );
  REQUIRE( l.size() == 0 );
}

TEST_CASE( "Create a list; WITH initializer list" ) {
  List l{84, 53, 2, 4, 99, 56, 6, 55, 55, 10, 20};
  l.insert(2);

  REQUIRE_FALSE( l.is_empty() == true );
  REQUIRE_FALSE( l.size() == 0 );
  l.print();

}
  
TEST_CASE( "Create a list; WITHOUT initializer list" ) {
  List l;

  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 9);
  for(int n{0}; n < 10; ++n) {
        l.insert(dist(rd));
    }

  REQUIRE_FALSE( l.is_empty() == true );
  REQUIRE_FALSE( l.size() == 0 );
}


TEST_CASE( "Stress Test" ) {
  List l{};

  std::random_device rd;
  std::uniform_int_distribution<unsigned int> dist(0, 9);
  int limit{100};

  for(int n{0}; n < limit; ++n) {
        l.insert(dist(rd));
    }

  REQUIRE_FALSE( l.is_empty() == true );
  REQUIRE( l.size() == limit );
}

TEST_CASE( "Test Copy Constructor" ) {
  List l;

  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 9);
  int limit{100};

  for(int n{0}; n < limit; ++n) {
        l.insert(dist(rd));
    }

  List empty = l;

  REQUIRE_FALSE( empty.is_empty() == true );
  REQUIRE( empty.size() == limit );
}

TEST_CASE( "Test Copy Assignment" ) {
  List l;

  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 9);
  int limit{100};

  for(int n = 0; n < limit; ++n) {
        l.insert(dist(rd));
    }

  List empty2{};
  empty2 = l;

  REQUIRE_FALSE( empty2.is_empty() == true );
  REQUIRE( empty2.size() == limit );
}

List get_list()
{
    List some_list{3, 2, 1};
    return some_list;
}

TEST_CASE( "Test Move Assignment" ) {
  List empty3;
  empty3 = get_list();

  REQUIRE_FALSE( empty3.is_empty() == true );
  REQUIRE_FALSE( empty3.size() == 0 );
}


List get_list2(List in)
{
    return in;
}

TEST_CASE( "Test Move Constructor" ) {
  List l{1,6,5,3};
  List empty4 = get_list2(l);

  REQUIRE_FALSE( empty4.is_empty() == true );
  REQUIRE_FALSE( empty4.size() == 0 );
} 

TEST_CASE( "Test Remove: remove by (zero-)index." ) {
  List l {1,6,5,3,6,3};
  std::cout << "TEST 'Remove': List proior to remove(x):" << std::endl;
  l.print();

  std::cout << "...and after removal index pos. 3:" << std::endl;
  // Remove item @ index 3 i.e 1, 3, 3, [[5]], 6, 6
  l.remove(3);
  l.print();

  REQUIRE_FALSE( l.is_empty() == true );
  REQUIRE( l.size() == 5 );
} 

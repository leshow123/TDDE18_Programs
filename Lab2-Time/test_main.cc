#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Operators.h"
//#include "Time.h"

#include <string>

TEST_CASE( "Test function is_valid()" ) {
  Time t{-18, 20, 10};
  REQUIRE( t.is_valid() == false );
} 

// Note: Midnight and Mid-day have no suffix in 12 hr format 

TEST_CASE( "Test function to_string(); default 24-hour format" ) {
  Time t{19, 25, 40};
  REQUIRE( t.to_string().length() == 8 );
} 

TEST_CASE( "Test function to_string(); 12-hour format" ) {
  Time t{19, 25, 40};
  REQUIRE( t.to_string(12).length() == 11 );
} 

TEST_CASE( "1. Test function is_am()" ) {
  Time t{15, 25, 40};
  REQUIRE( t.is_am() == "pm" );
} 

TEST_CASE( "2. Test function is_am()" ) {
  Time t{04, 25, 40};
  REQUIRE( t.is_am() == "am" );
} 

TEST_CASE( "Test operator+ and operator-" ) {
  Time t{};
  REQUIRE( (t+5).to_string() == "00:00:05" );
  REQUIRE( t.to_string() == "00:00:00" );
  Time t2 = t+5;
  REQUIRE( (t2-5).to_string() == "00:00:00" );
  REQUIRE( t2.to_string() == "00:00:05" ); 
}  

TEST_CASE( "Test POSTFIX operator++ and operator--" ) {
  Time t{};
  Time copy_prior_inc = t++;
  std::cout<< "teeeee..." << t.to_string() << std::endl; 
  // test the logic
  REQUIRE( copy_prior_inc.to_string() == "00:00:00" );
  REQUIRE( (t++).to_string() == "00:00:01" );
  REQUIRE_FALSE( t.to_string() == "00:00:00" );
  Time t2 = t++;
  Time copy_prior_dec = t2--;
  REQUIRE( copy_prior_dec.to_string() == "00:00:02" ); 
  REQUIRE( (t2--).to_string() == "00:00:01" );
} 

TEST_CASE( "Test PREFIX operator++ and operator--" ) {
  Time t{};
  Time inc_then_copy = ++t;
  REQUIRE( inc_then_copy.to_string() == "00:00:01" ); 
  REQUIRE( (++t).to_string() == "00:00:02" );
  Time t2 = ++t;
  Time dec_then_copy = --t2;
  REQUIRE( dec_then_copy.to_string() == "00:00:02" ); 
  REQUIRE( (--t2).to_string() == "00:00:01" ); 
} 

TEST_CASE( "Test operator<<" ) {
  Time t{18, 20, 10};
  REQUIRE( (std::cout << t << "\n").good() == true );
} 

TEST_CASE( "Test operator>>" ) {
  Time t;
  REQUIRE( (std::cin >> t).good() == true );
} 

TEST_CASE( "Test Comparison operators" ) {
  Time t{15, 02, 55};
  Time s{18, 20, 10};
  REQUIRE( t<s );
  REQUIRE_FALSE( t>s );
  REQUIRE_FALSE( t==s );
  REQUIRE( t!=s );
  REQUIRE( t<=s );
  REQUIRE_FALSE( t>=s );
} 




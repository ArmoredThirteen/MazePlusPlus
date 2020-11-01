#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"


TEST_CASE("True") {
  REQUIRE (true == true);
}

TEST_CASE("False") {
  REQUIRE (true == false);
}

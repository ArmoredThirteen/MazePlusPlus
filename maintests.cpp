#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include <iostream>

#include "MazeMap.h"
#include "Backtrack.h"


TEST_CASE("Initialized dimensions", "[MazeMap]") {
  int xLen = 5;
  int yLen = 2;

  MazeMap maze(xLen, yLen);

  SECTION("Total number of cells") {
    REQUIRE (maze.cells.size() == xLen * yLen * 2);
  }

  SECTION("Check dimensions using IsIndexValid()") {
    REQUIRE (maze.IsIndexValid  (0, 0));
    REQUIRE (maze.IsIndexValid  (4, 1));
    REQUIRE (!maze.IsIndexValid (-1, 0));
    REQUIRE (!maze.IsIndexValid (0, -1));
    REQUIRE (!maze.IsIndexValid (-1, -1));
    REQUIRE (!maze.IsIndexValid (5, 1));
    REQUIRE (!maze.IsIndexValid (4, 2));
    REQUIRE (!maze.IsIndexValid (5, 2));
  }
}


TEST_CASE ("Throw exceptions", "[MazeMap]") {
  int xLen = 5;
  int yLen = 2;

  MazeMap maze(xLen, yLen);

  SECTION("GetAt() and SetAt() throw out of range") {
    // GetAt(), negative index
    bool caught = false;
    try {
      maze.GetAt(-10, -10, 0);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE (caught);

    // GetAt(), high index
    caught = false;
    try {
      maze.GetAt(10, 10, 0);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE (caught);

    // SetAt(), negative index
    caught = false;
    try {
      maze.SetAt(-10, -10, 0, true);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE (caught);


    // SetAt(), high index
    caught = false;
    try {
      maze.SetAt(10, 10, 0, true);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE (caught);
  }
}

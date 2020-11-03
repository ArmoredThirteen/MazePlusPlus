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
    REQUIRE(maze.cells.size() == xLen * yLen * 2);
  }

  SECTION("Check dimensions using IsIndexValid()") {
    REQUIRE(maze.IsIndexValid  (0, 0));
    REQUIRE(maze.IsIndexValid  (4, 1));
    REQUIRE(!maze.IsIndexValid (-1, 0));
    REQUIRE(!maze.IsIndexValid (0, -1));
    REQUIRE(!maze.IsIndexValid (-1, -1));
    REQUIRE(!maze.IsIndexValid (5, 1));
    REQUIRE(!maze.IsIndexValid (4, 2));
    REQUIRE(!maze.IsIndexValid (5, 2));
  }
}


TEST_CASE("Manual SetAt(), check with GetAt()", "[MazeMap]") {
  int xLen = 3;
  int yLen = 3;

  SECTION("Path along lower corner") {
    MazeMap maze(xLen, yLen);

    // Build maze with walls broken in path along 0 x/y axis
    for (int x = 0; x < xLen; x++)
      for (int y = 0; y < yLen; y++) {
        if (x == 0)
          maze.SetAt(x, y, 0, false);
        if (y == 0)
          maze.SetAt(x, y, 1, false);
      }

    // Check all cells for correct broken paths
    for (int x = 0; x < xLen; x++)
      for (int y = 0; y < yLen; y++) {
        if (x > 0 && y > 0) {
          REQUIRE(maze.GetAt(x, y, 0));
          REQUIRE(maze.GetAt(x, y, 1));
        }
        if (x == 0)
          REQUIRE(!maze.GetAt(x, y, 0));
        if (y == 0)
          REQUIRE(!maze.GetAt(x, y, 1));
      }
  }

  SECTION("BreakWallBetween() along x axis") {
    MazeMap maze(xLen, yLen);

    for (int x = 1; x < xLen; x++)
      for (int y = 0; y < yLen; y++) {
        maze.BreakWallBetween(x - 1, y, x, y);
      }

    for (int x = 0; x < xLen; x++)
      for (int y = 0; y < yLen; y++) {
        REQUIRE(maze.GetAt(x, y, 0));
        REQUIRE(!maze.GetAt(x, y, 1));
      }
  }
}


TEST_CASE("Throw exceptions", "[MazeMap]") {
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
    REQUIRE(caught);

    // GetAt(), high index
    caught = false;
    try {
      maze.GetAt(10, 10, 0);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE(caught);

    // SetAt(), negative index
    caught = false;
    try {
      maze.SetAt(-10, -10, 0, true);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE(caught);

    // SetAt(), high index
    caught = false;
    try {
      maze.SetAt(10, 10, 0, true);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE(caught);
  }

  SECTION("BreakWallX() and BreakWallY() throw out of range") {
    // BreakWallX(), negative index
    bool caught = false;
    try {
      maze.BreakWallX(-10, -10);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE(caught);

    // BreakWallX(), high index
    caught = false;
    try {
      maze.BreakWallX(10, 10);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE(caught);

    // BreakWallY(), negative index
    caught = false;
    try {
      maze.BreakWallY(-10, -10);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE(caught);

    // BreakWallY(), high index
    caught = false;
    try {
      maze.BreakWallY(10, 10);
    }
    catch(const std::out_of_range& ex) {
      caught = true;
    }
    REQUIRE(caught);
  }
}

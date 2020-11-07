#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include <iostream>
#include <array>

#include "MazeMap.h"
#include "Backtrack.h"

using std::vector;


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

  SECTION("Initialized map") {
    MazeMap maze(xLen, yLen);

    for (int x = 0; x < xLen; x++)
      for (int y = 0; y < yLen; y++) {
        REQUIRE(maze.GetAt(x, y, 0));
        REQUIRE(maze.GetAt(x, y, 1));
      }
  }

  SECTION("Path along lower corner") {
    MazeMap maze(xLen, yLen);

    // Build maze with walls broken in path along 0 x/y axis
    for (int x = 0; x < xLen; x++)
      for (int y = 0; y < yLen; y++) {
        if (x == 0)
          maze.SetAt(x, y, 1, false);
        if (y == 0)
          maze.SetAt(x, y, 0, false);
      }

    // Check all cells for correct broken paths
    for (int x = 0; x < xLen; x++)
      for (int y = 0; y < yLen; y++) {
        if (x > 0 && y > 0) {
          REQUIRE(maze.GetAt(x, y, 0));
          REQUIRE(maze.GetAt(x, y, 1));
        }
        if (x == 0)
          REQUIRE(!maze.GetAt(x, y, 1));
        if (y == 0)
          REQUIRE(!maze.GetAt(x, y, 0));
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
        REQUIRE(maze.GetAt(x, y, 1));
        if (x == 0)
          REQUIRE(maze.GetAt(x, y, 0));
        else
          REQUIRE(!maze.GetAt(x, y, 0));
      }
  }

  SECTION("BreakWallBetween() along y axis") {
    MazeMap maze(xLen, yLen);

    for (int x = 0; x < xLen; x++)
      for (int y = 1; y < yLen; y++) {
        maze.BreakWallBetween(x, y - 1, x, y);
      }

      for (int x = 0; x < xLen; x++)
        for (int y = 0; y < yLen; y++) {
          REQUIRE(maze.GetAt(x, y, 0));
          if (y == 0)
            REQUIRE(maze.GetAt(x, y, 1));
          else
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


TEST_CASE("Helper methods", "[Backtrack]") {
  SECTION("Check OrderMoveDirs() ratio") {
    // Set random seed
    srand(time(NULL));

    // How many times to run OrderMoveDirs() to add to counts
    int orderingOperations = 120;
    // orderingOperations * 4 (number of move dirs) / 16 (values in table)
    float expectedCounts = (float)orderingOperations / (float)4;
    // Maximum average variance to succeed test
    float allowedVariance = 0.1;

    std::array<int, 4> weights = { 1, 1, 1, 1 };
    // First index is the move dir, second is the position it was ordered to
    vector<vector<int>> dirCounts(4, vector<int>(4, 0));

    // Count the number of times each number shows in each position
    for (int op = 0; op < orderingOperations; op++) {
      vector<int> moveDirs = Backtrack::GetMoveDirs(weights);
      for (int i = 0; i < 4; i++)
        dirCounts[moveDirs[i]][i]++;
    }

    // Backtrack is full random and should have equal spread
    float averageRatioVariance = 0;
    for (int i = 0; i < 4; i++)
      for (int k = 0; k < 4; k++) {
        std::cout << dirCounts[i][k] << "/" << (float)dirCounts[i][k]/(float)(expectedCounts) << " ";
        float ratio = (float)dirCounts[i][k]/(float)(expectedCounts);
        averageRatioVariance = std::abs(1 - ratio);
      }

    averageRatioVariance /= 16.0;
    std::cout << std::endl << averageRatioVariance;
    REQUIRE(averageRatioVariance <= allowedVariance);
  }

  SECTION("MoveDirToIncrement()") {
    int valsToTest = 20;
    for (int i = 0; i < valsToTest; i++) {
      int increment = Backtrack::MoveDirToIncrement(i);
      if (i % 2 == 0)
        REQUIRE(increment == -1);
      else
        REQUIRE(increment == 1);
    }
  }
}

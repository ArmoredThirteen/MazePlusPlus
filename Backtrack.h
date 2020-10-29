#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>

#include "MazeMap.h"


class Backtrack {
	public:
		static void Generate(MazeMap &maze);

	private:
		static void Recurse(MazeMap &maze, std::vector<bool> &visited, int x, int y);
		static int GetNextX(int moveDir, int x);
		static int GetNextY(int moveDir, int y);
		static bool CanMoveTo(MazeMap &maze, std::vector<bool> &visited, int x, int y)
		static void BreakNextWall(MazeMap &maze, int x, int y, int nextX, int nextY);
};

#endif

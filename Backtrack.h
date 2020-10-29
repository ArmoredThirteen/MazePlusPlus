#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>

#include "MazeMap.h"


class Backtrack {
	public:
		static void Generate(MazeMap &maze);

	private:
		static void Recurse(MazeMap &maze, std::vector<bool> &visited, int x, int y);
		static int MoveDirToIncrement(int moveDir);
		static bool CanMoveTo(MazeMap &maze, std::vector<bool> &visited, int x, int y);
		static void BreakNextWall(MazeMap &maze, int x, int y, int nextX, int nextY);
};

#endif

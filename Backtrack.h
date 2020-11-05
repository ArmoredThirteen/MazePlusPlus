#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>

#include "MazeMap.h"


class Backtrack {
	public:
		static void Generate(MazeMap &maze);

		static void OrderMoveDirs(int moveDirs[]);
		static int MoveDirToIncrement(int moveDir);
		static bool CanMoveTo(MazeMap &maze, std::vector<bool> &visited, int x, int y);

	private:
		static void Recurse(MazeMap &maze, std::vector<bool> &visited, int x, int y);
};

#endif

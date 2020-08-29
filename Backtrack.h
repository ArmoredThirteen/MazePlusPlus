#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>

#include "MazeMap.h"


class Backtrack {
	public:
		static void Generate(MazeMap &maze);

	private:
		static void Recurse(MazeMap &maze, std::vector<bool> &visited, int x, int y);
		static bool IsVisited(std::vector<bool> &visited, int xLen, int x, int y);
};

#endif
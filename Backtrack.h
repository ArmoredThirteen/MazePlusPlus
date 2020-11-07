#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>
#include <array>

#include "MazeMap.h"


class Backtrack {
	public:
		static void Generate(MazeMap &maze);
		static void Generate(MazeMap &maze, std::array<int, 4> &weights, int startX, int startY);

		static std::vector<int> GetMoveDirs(std::array<int, 4> &weights);
		static int MoveDirToIncrement(int moveDir);
		static bool CanMoveTo(MazeMap &maze, std::vector<bool> &visited, int x, int y);

	private:
		static void Recurse(MazeMap &maze, std::vector<bool> &visited, std::array<int, 4> &weights, int x, int y);
};

#endif

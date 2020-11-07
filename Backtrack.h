#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>
#include <array>

#include "MazeMap.h"


class Backtrack {
	public:
		static void Generate(MazeMap &maze);
		static void Generate(MazeMap &maze, int startX, int startY, std::array<int, 4> weights);

		static std::vector<int> GetMoveDirs(std::array<int, 4> &weights);
		static int MoveDirToIncrement(int moveDir);
		static bool CanMoveTo(MazeMap &maze, std::vector<bool> &visited, int x, int y);

	private:
		static void Recurse(MazeMap &maze, std::vector<bool> &visited, int x, int y, std::array<int, 4> &weights);
};

#endif

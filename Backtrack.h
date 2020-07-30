#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>


class Backtrack {
public: static std::vector<bool> Generate(int rows, int cols);
private: static void Recurse(std::vector<bool> &maze, std::vector<bool> &visited, int rows, int cols, int x, int y);
private: static bool IsIndexValid(int rows, int cols, int x, int y);
private: static bool IsVisited(std::vector<bool> &visited, int xLen, int x, int y);
private: static void BreakWallX(std::vector<bool> &maze, int xLen, int yLen, int x, int y);
private: static void BreakWallY(std::vector<bool> &maze, int xLen, int yLen, int x, int y);
};

#endif
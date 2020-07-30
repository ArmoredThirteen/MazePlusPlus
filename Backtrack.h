#include <vector>

using namespace std;


class Backtrack {
	public: static vector<bool> Generate(int rows, int cols);
	private: static void Recurse(vector<bool> &maze, vector<bool> &visited, int rows, int cols, int x, int y);
	private: static bool IsIndexValid(int rows, int cols, int x, int y);
	private: static bool IsVisited(vector<bool> &visited, int xLen, int x, int y);
	private: static void BreakWallX(vector<bool> &maze, int xLen, int yLen, int x, int y);
	private: static void BreakWallY(vector<bool> &maze, int xLen, int yLen, int x, int y);
};
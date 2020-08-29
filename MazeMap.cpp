#include <stdlib.h> /* srand, rand */
#include <iostream>

#include "MazeMap.h"

using std::vector;


int xLen;
int yLen;
vector<bool> cells;


MazeMap::MazeMap(int theXLen, int theYLen) {
	xLen = theXLen;
	yLen = theYLen;
	cells = vector<bool> (xLen * yLen * 2, true);
}

//TODO: Evaluate if anything has to happen here
MazeMap::~MazeMap() {}


// True if given x,y are within the bounds of xLen,yLen
bool MazeMap::IsIndexValid(int x, int y) {
	if (x < 0 || x >= xLen)
		return false;
	if (y < 0 || y >= yLen)
		return false;
	return true;
}

// Breaks the x-axis wall in cell at x,y (sets bit 0 to be false)
void MazeMap::BreakWallX(int x, int y) {
	//cells[x + (y * xLen) + (0 * xLen * yLen)] = false;
	cells[x + (y * xLen)] = false;
}

// Breaks the y-axis wall in cell at x,y (sets bit 1 to be false)
void MazeMap::BreakWallY(int x, int y) {
	//cells[x + (y * xLen) + (1 * xLen * yLen)] = false;
	cells[x + (y * xLen) + (xLen * yLen)] = false;
}


std::ostream& operator<< (std::ostream& strm, MazeMap& maze) {
	for (int y = 0; y < maze.yLen; y++) {
		for (int x = 0; x < maze.xLen; x++) {
			for (int z = 0; z < 2; z++) {
				strm << maze.cells[x + (y * maze.xLen) + (z * maze.xLen * maze.yLen)];
			}
			if (x < maze.xLen - 1)
				strm << "-";
		}
		if (y < maze.yLen - 1)
			strm << "|";
	}

	return strm;
}
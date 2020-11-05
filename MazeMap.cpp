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


bool MazeMap::GetAt(int x, int y, int wallIndex) {
	if (!IsIndexValid(x, y))
		throw std::out_of_range ("GetAt() given invalid x,y index(es)");
	return cells[x + (y * xLen) + (wallIndex * xLen * yLen)];
}

void MazeMap::SetAt(int x, int y, int wallIndex, bool isWall) {
	if (!IsIndexValid(x, y))
		throw std::out_of_range ("SetAt() given invalid x,y index(es)");
	cells[x + (y * xLen) + (wallIndex * xLen * yLen)] = isWall;
}


// Breaks the x-axis wall in cell at x,y (sets bit 0 to be false)
void MazeMap::BreakWallX(int x, int y) {
	SetAt(x, y, 0, false);
}

// Breaks the y-axis wall in cell at x,y (sets bit 1 to be false)
void MazeMap::BreakWallY(int x, int y) {
	SetAt(x, y, 1, false);
}

// Calls BreakWallX/Y to break the wall between the current and next cells
// Depending on direction the changed cell is either at location one or two
void MazeMap::BreakWallBetween(int xOne, int yOne, int xTwo, int yTwo) {
	// Break appropriate x-axis wall
	if (xTwo < xOne)
		BreakWallX(xOne, yOne);
	else if (xTwo > xOne)
		BreakWallX(xTwo, yOne);
	// Break appropriate y-axis wall
	else if (yTwo < yOne)
		BreakWallY(xOne, yOne);
	else if (yTwo > yOne)
		BreakWallY(xOne, yTwo);
}


std::ostream& operator<< (std::ostream& strm, MazeMap& maze) {
	for (int y = 0; y < maze.yLen; y++) {
		for (int x = 0; x < maze.xLen; x++) {
			for (int z = 0; z < 2; z++) {
				strm << maze.GetAt(x, y, z);
			}
			if (x < maze.xLen - 1)
				strm << "-";
		}
		if (y < maze.yLen - 1)
			strm << "|";
	}

	return strm;
}

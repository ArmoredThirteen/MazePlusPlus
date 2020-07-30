#include <iostream>
#include <vector>
#include <stdlib.h> /* srand, rand */
#include "Backtrack.h"

using namespace std;


/*
 * Generates a maze using a recursive backtrack method.
 * Crawler randomly moves to an adjacent cell and marks it visited.
 * As it moves, appropriate walls are knocked down.
 * Once it has no unvisited choices, it bubbles up.
 * Eventually it bubbles up to a cell where there is another adjacent unvisited cell.
 * Keeps doing this until it bubbles all the way back up and recursion ends.
 */
vector<bool> Backtrack::Generate(int xLen, int yLen) {
	vector<bool> maze(xLen * yLen * 2, true);
	vector<bool> visited(xLen * yLen, false);
	Backtrack::Recurse(maze, visited, xLen, yLen, 0, 0);

	return maze;
}

void Backtrack::Recurse(vector<bool> &maze, vector<bool> &visited, int xLen, int yLen, int x, int y) {
	// Mark current as visited
	visited[x + (y * xLen)] = true;

	// Randomized move directions
	int moveDirs[4] = { 0,1,2,3 };
	for (int i = 0; i < 4; i++) {
		int swapInd = rand() % 4;
		int temp = moveDirs[swapInd];
		moveDirs[swapInd] = moveDirs[i];
		moveDirs[i] = temp;
	}

	// Attempt each moveDir
	for (int i = 0; i < 4; i++) {
		int moveDir = moveDirs[i];

		// Determine indexes of next move direction
		int nextX = x;
		int nextY = y;

		if (moveDir == 0)
			nextX = x + 1;
		else if (moveDir == 1)
			nextX = x - 1;
		else if (moveDir == 2)
			nextY = y + 1;
		else if (moveDir == 3)
			nextY = y - 1;

		// Early exit if can't move that direction
		if (!IsIndexValid(xLen, yLen, nextX, nextY))
			continue;
		if (IsVisited(visited, xLen, nextX, nextY))
			continue;

		// Break appropriate x-axis wall
		if (nextX < x)
			BreakWallX(maze, xLen, yLen, x, y);
		else if (nextX > x)
			BreakWallX(maze, xLen, yLen, nextX, y);

		// Break appropriate y-axis wall
		if (nextY < y)
			BreakWallY(maze, xLen, yLen, x, y);
		else if (nextY > y)
			BreakWallY(maze, xLen, yLen, x, nextY);
		
		// Dig into the next cell
		Recurse(maze, visited, xLen, yLen, nextX, nextY);
	}
}


// True if given x,y are within the bounds of xLen,yLen
bool Backtrack::IsIndexValid(int xLen, int yLen, int x, int y) {
	if (x < 0 || x >= xLen)
		return false;
	if (y < 0 || y >= yLen)
		return false;
	return true;
}

// True if cell at x,y has already been visited
bool Backtrack::IsVisited(vector<bool> &visited, int xLen, int x, int y) {
	return visited[x + (y * xLen)];
}


// Breaks the x-axis wall in cell at x,y (sets bit 0 to be false)
void Backtrack::BreakWallX(vector<bool> &maze, int xLen, int yLen, int x, int y) {
	maze[x + (y * xLen) + (0 * xLen * yLen)] = false;
}

// Breaks the y-axis wall in cell at x,y (sets bit 1 to be false)
void Backtrack::BreakWallY(vector<bool> &maze, int xLen, int yLen, int x, int y) {
	maze[x + (y * xLen) + (1 * xLen * yLen)] = false;
}
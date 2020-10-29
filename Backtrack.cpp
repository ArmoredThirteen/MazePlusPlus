#include <stdlib.h> /* srand, rand */

#include "Backtrack.h"

using std::vector;


/*
 * Attempts to generate a maze using a recursive backtrack method.
 * Crawler randomly moves to an adjacent cell and marks it visited.
 * As it moves, appropriate walls are knocked down.
 * Once it has no unvisited choices, it bubbles up.
 * Eventually it bubbles up to a cell where there is another adjacent unvisited cell.
 * Keeps doing this until it bubbles all the way back up and recursion ends.
 */
void Backtrack::Generate(MazeMap &maze) {
	vector<bool> visited(maze.xLen * maze.yLen, false);
	Backtrack::Recurse(maze, visited, 0, 0);
}

void Backtrack::Recurse(MazeMap &maze, vector<bool> &visited, int x, int y) {
	// Mark current as visited
	visited[x + (y * maze.xLen)] = true;

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
		// Determine indexes of next move direction
		int nextX = moveDirs[i] > 1 ? x : x + GetNextX(moveDirs[i]);
		int nextY = moveDirs[i] < 2 ? y : y + GetNextY(moveDirs[i]);

		// Early exit if can't move that direction
		if (!CanMoveTo(maze, visited, nextX, nextY))
			continue;

		// Break wall between this cell and the next
		BreakNextWall(maze, x, y, nextX, nextY);

		// Move to the next cell
		Recurse(maze, visited, nextX, nextY);
	}
}


int Backtrack::MoveDirToIncrement(int moveDir) {
	return ((moveDir % 2) * 2) - 1;
}


// True if cell at (x,y) has a valid index and has not been visited
bool Backtrack::CanMoveTo(MazeMap &maze, vector<bool> &visited, int x, int y) {
	return maze.IsIndexValid(x, y) && !visited[x + (y * maze.xLen)];
}


// Calls maze.BreakWallX/Y to break the wall between the current and next cells
// Depending on direction the changed cell is either at (x,y) or (nextX,nextY)
void Backtrack::BreakNextWall(MazeMap &maze, int x, int y, int nextX, int nextY) {
	// Break appropriate x-axis wall
	if (nextX < x)
		maze.BreakWallX(x, y);
	else if (nextX > x)
		maze.BreakWallX(nextX, y);
	// Break appropriate y-axis wall
	else if (nextY < y)
		maze.BreakWallY(x, y);
	else if (nextY > y)
		maze.BreakWallY(x, nextY);
}

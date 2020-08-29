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
		if (!maze.IsIndexValid(nextX, nextY))
			continue;
		if (IsVisited(visited, maze.xLen, nextX, nextY))
			continue;

		// Break appropriate x-axis wall
		if (nextX < x)
			maze.BreakWallX(x, y);
		else if (nextX > x)
			maze.BreakWallX(nextX, y);

		// Break appropriate y-axis wall
		if (nextY < y)
			maze.BreakWallY(x, y);
		else if (nextY > y)
			maze.BreakWallY(x, nextY);
		
		// Dig into the next cell
		Recurse(maze, visited, nextX, nextY);
	}
}

// True if cell at x,y has already been visited
bool Backtrack::IsVisited(vector<bool> &visited, int xLen, int x, int y) {
	return visited[x + (y * xLen)];
}
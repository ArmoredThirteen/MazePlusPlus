#include <stdlib.h> /* srand, rand */
#include <algorithm>

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
	vector<int> moveDirs = GetMoveDirs({ 1, 1, 1, 1 });

	// Attempt each moveDir
	for (int i = 0; i < 4; i++) {
		// Determine indexes of next move direction
		int nextX = moveDirs[i] > 1 ? x : x + MoveDirToIncrement(moveDirs[i]);
		int nextY = moveDirs[i] < 2 ? y : y + MoveDirToIncrement(moveDirs[i]);

		// Early exit if can't move that direction
		if (!CanMoveTo(maze, visited, nextX, nextY))
			continue;

		// Break wall between this cell and the next
		maze.BreakWallBetween(x, y, nextX, nextY);

		// Move to the next cell
		Recurse(maze, visited, nextX, nextY);
	}
}


vector<int> Backtrack::GetMoveDirs(std::array<int, 4> weights) {
	int dirsCount = 0;
	vector<int> weightedDirs;

	// Add each dir a number of times according to dirWeights[]
	for (int i = 0; i < 4; i++) {
		dirsCount += weights[i];
		for (int dir = 0; dir < weights[i]; dir++)
			weightedDirs.push_back(i);
	}

	// Randomize the weightedDirs
	for (int i = 0; i < dirsCount; i++) {
		int swapInd = rand() % dirsCount;
		int temp = weightedDirs[swapInd];
		weightedDirs[swapInd] = weightedDirs[i];
		weightedDirs[i] = temp;
	}

	// Populate returnDirs with one of each dir based on which is found first
	vector<int> returnDirs;
	for (int i = 0; i < dirsCount; i++) {
		// If current weightedDirs does not exist in returnDirs
		if (std::find(returnDirs.begin(), returnDirs.end(), weightedDirs[i]) == returnDirs.end())
			returnDirs.push_back(weightedDirs[i]);
	}

	return returnDirs;
}

int Backtrack::MoveDirToIncrement(int moveDir) {
	return ((moveDir % 2) * 2) - 1;
}

// True if cell at (x,y) has a valid index and has not been visited
bool Backtrack::CanMoveTo(MazeMap &maze, vector<bool> &visited, int x, int y) {
	return maze.IsIndexValid(x, y) && !visited[x + (y * maze.xLen)];
}

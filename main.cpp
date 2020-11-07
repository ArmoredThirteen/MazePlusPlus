#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <iostream>

#include "MazeMap.h"
#include "Backtrack.h"

using std::cout;
using std::vector;
using std::string;


/*
 * Receives [(string)genMethod, (int)seed, (int)xLen, (int)yLen, ...(gen specific args)].
 * Prints out the resulting maze's data (1s/0s for walls/paths plus seperators for cells and rows).
 */
int main(int argc, char *argv[])
{
	// Verify argument count (first arg is execution path)
	if (argc < 5) {
		cout << "Generation requires at least 4 arguments: [(string)genMethod, (int)seed, (int)xLen, (int)yLen]";
		return -1;
	}

	// Cast arguments
	string genMethod = string(argv[1]);
	int seed = atoi(argv[2]);
	int xLen = atoi(argv[3]);
	int yLen = atoi(argv[4]);

	// Verify lengths are usable
	if (xLen <= 0) {
		cout << "xLen is <= 0, cannot generate maze with missing dimension";
		return -1;
	}
	if (yLen <= 0) {
		cout << "yLen is <= 0, cannot generate maze with missing dimension";
		return -1;
	}

	// Set random seed
	srand(seed > 0 ? seed : time(NULL));

	// Initialize blank maze
	MazeMap maze(xLen, yLen);

	// Run appropriate generation over the maze
	if (genMethod == "backtrack") {
		int startX = atoi(argv[5]);
		int startY = atoi(argv[6]);

		int weightOne = atoi(argv[7]);
		int weightTwo = atoi(argv[8]);
		int weightThree = atoi(argv[9]);
		int weightFour = atoi(argv[10]);

		if (startX < 0 || startY < 0) {
			cout << "Starting x and y must be a positive number";
			return -1;
		}
		if (startX >= xLen || startY >= yLen) {
			cout << "Starting x and y must be lower than max maze dimensions"
			return -1;
		}
		if (weightOne < 1 || weightTwo < 1 || weightThree < 1 || weightFour < 1) {
			cout << "Move direction weights must be 1 or higher"
			return -1;
		}

		Backtrack::Generate(maze, startX, startY, { weightOne, weightTwo, weightThree, weightFour });
	}
	else {
		cout << "Could not find given maze generation method: " << argv[1];
		return -1;
	}

	// Print with separators
	cout << maze;

	return 0;
}

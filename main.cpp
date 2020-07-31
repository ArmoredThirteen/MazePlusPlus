#include <iostream>
#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include "Backtrack.h"

using std::cout;
using std::vector;
using std::string;


/*
 * Receives [(string)genMethod, (int)seed, (int)xLen, (int)yLen, ...(gen specific args)].
 * Prints out the resulting maze's data (1s/0s for walls/paths plus seperators for cells '-' and yLen '|').
 * Currently only creates backtrack mazes.
 * Designed to add more maze generation types with variety of settings.
 */
int main(int argc, char *argv[])
{
	// Verify argument count (first arg is execution path)
	if (argc < 4) {
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

	//TODO: Create additionalArgs count and array
	//		Trim argv to only include index 5 and later

	// Make maze
	// TODO: Maybe set function pointer here then do the actual maze creation after if/else
	vector<bool> maze;
	if (genMethod == "backtrack")
		maze = Backtrack::Generate(xLen, yLen, argc - 5, NULL);
	else {
		cout << "Could not find given maze generation method: " << argv[1];
		return -1;
	}

	// Print with separators
	for (int y = 0; y < yLen; y++) {
		for (int x = 0; x < xLen; x++) {
			for (int z = 0; z < 2; z++) {
				cout << maze[x + (y * xLen) + (z * xLen * yLen)];
			}
			if (x < xLen - 1)
				cout << "-";
		}
		if (y < yLen - 1)
			cout << "|";
	}

	return 0;
}
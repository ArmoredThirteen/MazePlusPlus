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

	//TODO: Create additionalArgs count and array
	//		This sub-array should only include the argv values at index 5 and up

	// Make maze
	//TODO: Maybe set function pointer here then do the actual maze creation after if/else
	//		Using data from the mentioned sub-array, which only has data for different generator types
	vector<bool> maze;
	if (genMethod == "backtrack")
		maze = Backtrack::Generate(xLen, yLen/*, subArrayLen, subArray*/);
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
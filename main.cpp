#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include "Backtrack.h"

using namespace std;


/*
 * Receives rows, cols, and seed.
 * Uses those to build appropriately sized mazes.
 * Currently only creates backtrack mazes.
 *   All except the one line calling backtrack is general purpose.
 */
int main(int argc, char *argv[])
{
	// Verify argument count
	if (argc != 4) {
		cout << "Requires 3 parameters: [rows,cols,seed]";
		return -1;
	}

	// Cast arguments
	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);
	int seed = atoi(argv[3]);

	// Verify given rows/cols is usable
	if (rows <= 0) {
		cout << "Rows <= 0, cannot generate maze without any rows";
		return -1;
	}
	if (cols <= 0) {
		cout << "Cols <= 0, cannot generate maze without any columns";
		return -1;
	}

	// Set random seed
	srand(seed > 0 ? seed : time(NULL));

	// Make maze
	vector<bool> maze = Backtrack::Generate(cols, rows);

	// Print with separators
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			for (int z = 0; z < 2; z++) {
				cout << maze[x + (y * cols) + (z * cols * rows)];
			}
			if (x < cols - 1)
				cout << "-";
		}
		if (y < rows - 1)
			cout << "|";
	}

	return 0;
}
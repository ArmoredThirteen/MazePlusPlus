#ifndef MAZEMAP_H
#define MAZEMAP_H

#include <iostream>
#include <vector>


class MazeMap {
	public:
		int xLen;
		int yLen;
		std::vector<bool> cells;

		MazeMap(int theXLen, int theYLen);
		~MazeMap();

		bool IsIndexValid(int x, int y);

		bool GetAt(int x, int y, int wallIndex);
		void SetAt(int x, int y, int wallIndex, bool isWall);

		void BreakWallX(int x, int y);
		void BreakWallY(int x, int y);
		void BreakWallBetween(int xOne, int yOne, int xTwo, int yTwo);

		friend std::ostream& operator<< (std::ostream&, MazeMap&);
};

#endif

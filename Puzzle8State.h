#ifndef STATE_8_PUZZLE_H
#define STATE_8_PUZZLE_H

#include <string>
#include <cassert>
#include <iostream>
#include <vector>

#include <cmath>

// Represents an 8-puzzle state as a 3x3 array of chars. Each char can take values in range '0'-'9' (chars, not integers).
// '0' represents the blank tile.
// Provides GetKey to uniquely represent the puzzle as an integer (for hashing).
// You can extend this class to generate successors and get heuristic distance to '012345678', which is always the goal state.

class Puzzle8State {
public:
	Puzzle8State(std::string s = "012345678") {
		assert(s.length() == 9);
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				tiles[r][c] = s[r*3 + c];
	}

	// Key generated as an integer for the hash function in Puzzle8StateManager.
	int GetKey() {
		int key = 0;
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				key = key*10 + int(tiles[r][c] - '0');
		return key;
	}

	// Return the linearized form as a string. (You don't need to use this.)
	std::string GetLinearizedForm () {
		std::string s = "";
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				s += tiles[r][c];
		return s;
	}

	// Print the puzzle in a 3x3 layout. (You don't need to use this.)
	void Print(std::ostream & out = std::cout) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				out<<tiles[r][c]<<" ";
			}
			out<<std::endl;
		}
		out<<GetKey()<<std::endl;
	}


	// Generate Successors
	std::vector<Puzzle8State> getSuccessors(){
		std::vector<Puzzle8State> successors;
		//find where the 0 is
		int row = -1;
		int column = -1;
		for(int r = 0; r < 3; r++){
			for(int c = 0; c < 3; c++){
				if(tiles[r][c] == '0'){
					row = r;
					column = c;
				}
			}
		}
		//swaping tiles to find successors
		if(row - 1 >= 0){
			char temp;
			temp = tiles[row -1][column];
			tiles[row -1][column] = tiles[row][column];
			tiles[row][column] = temp;

			Puzzle8State successor(this->GetLinearizedForm());
			successors.push_back(successor);

			temp = tiles[row-1][column];
			tiles[row -1][column] = tiles[row][column];
			tiles[row][column] = temp;
		}
		if(row + 1 <= 2){
			char temp;
			temp = tiles[row + 1][column];
			tiles[row +1][column] = tiles[row][column];
			tiles[row][column] = temp;

			Puzzle8State successor(this->GetLinearizedForm());
			successors.push_back(successor);

			temp = tiles[row+1][column];
			tiles[row +1][column] = tiles[row][column];
			tiles[row][column] = temp;
		}
		if(column + 1 <= 2){
			char temp;
			temp = tiles[row][column+1];
			tiles[row][column+1] = tiles[row][column];
			tiles[row][column] = temp;

			Puzzle8State successor(this->GetLinearizedForm());
			successors.push_back(successor);

			temp = tiles[row][column+1];
			tiles[row][column+1] = tiles[row][column];
			tiles[row][column] = temp;
		}
		if(column - 1 >= 0){
			char temp;
			temp = tiles[row][column-1];
			tiles[row][column-1] = tiles[row][column];
			tiles[row][column] = temp;

			Puzzle8State successor(this->GetLinearizedForm());
			successors.push_back(successor);

			temp = tiles[row][column-1];
			tiles[row][column-1] = tiles[row][column];
			tiles[row][column] = temp;
		}



		return successors;
	}




	//calcluate the heuristic for A* saerch
	int calculateHeuristic(){
		int sum = 0;
		for(int r = 0; r < 3; r++){
			for(int c = 0; c < 3; c++){
				switch (tiles[r][c]){
					case '8':
						sum += abs(2 - r) + abs(2 - c);
						break;
					case '7':
						sum += abs(2 - r) + abs(1 - c);
						break;
					case '6':
						sum += abs(2 - r) + abs(0 - c);
						break;
					case '5':
						sum += abs(1 - r) + abs(2 - c);
						break;
					case '4':
						sum += abs(1 - r) + abs(1 - c);
						break;
					case '3':
						sum += abs(1 - r) + abs(0 - c);
						break;
					case '2':
						sum += abs(0 - r) + abs(2 - c);
						break;
					case '1':
						sum += abs(0 - r) + abs(1 - c);
						break;
				}
			}
		}
		return sum;
	}


private:

	// tiles[r][c] is the tile (or blank) at row r (0-2) and column c (0-2)
	// 0th row is the top row, and 0th column is the leftmost column.
	char tiles[3][3];


};

#endif

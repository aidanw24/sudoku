#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

const int N = 9;
const int EMPTY = 0;

// returns true if number is found in the row
bool checkrow(int puzzle[N][N], int row, int num){
	for (int i = 0; i < N; ++i){
		if (num == puzzle[row][i]){
			return true;
		}
	}
	return false;
}
bool checkcolumn(int puzzle[N][N], int column, int num){
	for (int i = 0; i < N; ++i){
		if (num == puzzle[i][column]){
			return true;
		}
	}
	return false;
}

bool checkSquare(int puzzle[N][N], int startingRow, int startingColumn, int num){
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			if (num == puzzle[startingRow + i][startingColumn + j]){
				return true;
			}
		}
	}
	return false;
}


bool possible(int puzzle[N][N], int row, int column, int num){
	return !checkrow(puzzle, row, num) && !checkcolumn(puzzle, column, num) && !checkSquare(puzzle, row - row % 3, column - column % 3, num) && puzzle[row][column] == EMPTY;
}

bool findEmpty(int puzzle[N][N], int &row, int &column){
	for (row = 0; row < N; ++row){
		for (column = 0; column < N; ++column){
			if (puzzle[row][column] == EMPTY){
				return true;
			}
		}
	}
	return false;
}


bool solve(int puzzle[N][N]){
	int row, col;
	if (!findEmpty(puzzle, row, col)){ // if all squares are filled then return true
		cout << "Solved" << endl;
		return true;
	}
	for (int i = 1; i <= N; i++){
		if (possible(puzzle, row, col, i)){
			puzzle[row][col] = i;
			if (solve(puzzle)){
				return true;
			}
			puzzle[row][col] = EMPTY;
		}	
	}
	return false;
}

void printPuzzle(int puzzle[N][N]){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
}

void pastePuzzle(int puzzle[N][N]){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			cin >> puzzle[i][j];
		}
	}
}
void readFile(int puzzle[N][N]){
	ifstream inFile;
	inFile.open("puzzle.txt");
	if (!inFile){
		cout << "File not found" << endl;
		readFile(puzzle);
	}
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			inFile >> puzzle[i][j];
		}
	}
	inFile.close();
}
void readPuzzle(int puzzle[N][N]){
	int ans;
	cout << "Input 1 for pasting puzzle, input 2 for reading puzzle from puzzle.txt: ";
	cin >> ans;
	if (ans == 1){
		pastePuzzle(puzzle);
		return;
	}
	if (ans == 2) {
		readFile(puzzle);
		return;
	}
	else {
		readPuzzle(puzzle);
	}
}

int main(){
	int puzzle[N][N];
	readPuzzle(puzzle);
	if (!solve(puzzle)){
		cout << "Failed to solve" << endl;
	}
	else {
		printPuzzle(puzzle);		
	}
	system("pause");
}


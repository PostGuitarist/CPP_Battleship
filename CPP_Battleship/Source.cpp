//Include statements
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Function prototypes
void fire(char board[25][25], int x, int y);
bool fleetSunk(char board[25][25]);
void displayBoard(char userBoard[25][25]);
void refreshUserBoard(char board[25][25], char userBoard[25][25]);

int main()
{
	ifstream inFile;
	char board[25][25];
	char userBoard[25][25];
	int x{ 0 }, y{ 0 };

	//Program logic
	inFile.open("battleship.txt");
	if (!inFile) {
		cout << "Could not open file..." << endl;
	}
	else {
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				inFile >> board[i][j];
			}
		}

		cout << endl;

		refreshUserBoard(board, userBoard);
		displayBoard(userBoard);

		do {
			cout << "Enter an X and Y coordinate separated by a space: ";
			cin >> x >> y;


			fire(board, y, x); //X and Y are switched because of the way the board is read in
			cout << endl;
			refreshUserBoard(board, userBoard);
			displayBoard(userBoard);

		} while (!fleetSunk(board));

		cout << "The fleet was destroyed!" << endl << endl;
	}

	inFile.close();

	return 0;
}

void fire(char board[25][25], int x, int y) {
	x -= 1;
	y -= 1;

	if (board[x][y] == '~') {
		cout << "MISS" << endl;
		board[x][y] = 'M';
	}
	else if (board[x][y] == '#') {
		cout << "HIT" << endl;
		board[x][y] = 'H';
	}
	else if (board[x][y] == 'H') {
		cout << "HIT AGAIN" << endl;
	}
}

bool fleetSunk(char board[25][25]) {
	bool sunk = true;
	for (int i = 0; i < 25; i++) {
		for (int k = 0; k < 25; k++) {
			if (board[i][k] == '~') {
				sunk = true;
				continue;
			}
			else if (board[i][k] == 'H') {
				sunk = true;
				continue;
			}
			else if (board[i][k] == 'M') {
				sunk = true;
				continue;
			}
			else if (board[i][k] == '#') {
				sunk = false;
				break;
			}
		}
		if (sunk == false) {
			break;
		}
	}
	return sunk;
}

void displayBoard(char userBoard[25][25]) {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			cout << userBoard[i][j];
		}
		cout << endl;
	}
}

void refreshUserBoard(char board[25][25], char userBoard[25][25]) {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			userBoard[i][j] = '~';
		}
	}

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			if (board[i][j] == 'H') {
				userBoard[i][j] = 'H';
			}
			else if (board[i][j] == 'M') {
				userBoard[i][j] = 'M';
			}
		}
	}
}
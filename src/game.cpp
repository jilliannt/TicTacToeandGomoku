/*
* Author: Jillian Tarlowe
* Purpose: Definitions for functions used in the game
*/

#include "game.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

TicTacToeGame::TicTacToeGame() {
	size = 5;
	for (int i = 0; i < size * size; ++i) { //populates the vector with empty game pieces
		vec.push_back(" ");
	}
	longestPiece = 1;
}

TicTacToeGame::~TicTacToeGame() {
}

bool TicTacToeGame::done() {
	if ((vec[12] != " ") && (vec[12] == vec[16]  && vec[8] == vec[16])) { //left diagonal
		return true;
	}

	if ((vec[12] != " ") && (vec[12] ==  vec[6] && vec[18] == vec[6])) { //right diagonal
		return true;
	}
	if ((vec[16] != " ") && (vec[16] == vec[11] && vec[6] == vec[11])) { //left vertical
		return true;
	}
	if ((vec[17] != " ") && (vec[17] ==  vec[12]  && vec[7] == vec[12])) { //mid vertical
		return true;
	}
	if ((vec[18] != " ") && (vec[18] ==  vec[13]  && vec[8] == vec[13])) { //right vertical
		return true;
	}
	if ((vec[16] != " ") && (vec[16] == vec[17]  && vec[18] == vec[17])) { //top horizontal
		return true;
	}
	if ((vec[11] != " ") && (vec[11] == vec[12]  && vec[13] == vec[12])) { //mid horizontal
		return true;
	}
	if ((vec[8] != " ") && (vec[6] == vec[7] && vec[7] == vec[8])){ //bottom horizontal
		return true;
	}
	return false;
}

bool TicTacToeGame::draw() {
	if (done() == false && movesleft == false) {
		return true;
	}
	return false;
}

int GameBase::prompt(unsigned int& x, unsigned int& y) {
	cout << "Please type a valid pair of indices or 'quit' to end the game." << endl;
	string input;
	getline(cin, input);
	if (input == "quit") {
		promptreturn = (int)returns::QUIT;
		return (int)returns::QUIT;
	}
	if (input.find(",") != -1) { // checks that there is a comma present
		input.replace(input.find(","), 1, " ");
		istringstream whole(input);
		if (whole >> x && whole >> y) { //checks that there are two numbers to pass to the variables
			if (size == 5) {
				if ((0 < x && x < 4) && (0 < y && y < 4) && (vec[size * (y) + x] == " ")) {
					promptreturn = (int)returns::SUCCESS;
					return (int)returns::SUCCESS;
				}
			}
			else {
				if ((0 < x && x <= size) && (0 < x && y <= size) && (vec[size * (y - 1) + x - 1] == " ")) {
					promptreturn = (int)returns::SUCCESS;
					return (int)returns::SUCCESS;
				}
			}
		}
	}
	prompt(x, y);
}

GameBase* GameBase::objectConstruct(int argc, char* argv[]) {
	if (argc == 2) {
		string givenName = argv[1];
		if (givenName.compare("TicTacToe") == 0) {
			TicTacToeGame* ttt = new TicTacToeGame();
			return ttt;
		}
		if (givenName.compare("Gomoku") == 0) {
			GomokuGame* gg = new GomokuGame();
			return gg;
		}
	}
	return nullptr;
}

int TicTacToeGame::turn() {
	cout << endl;
	cout << curPlayer << ", it's your turn!" << endl;
	prompt(x, y);
	if (promptreturn == (int)returns::QUIT) {
		return (int)returns::QUIT;
	}
	if (promptreturn == (int)returns::SUCCESS) {
		if (curPlayer == xPlay) {
			vec[size * y + x] = "X";
			xPlays += to_string(x);
			xPlays += ", ";
			xPlays += to_string(y);
			xPlays += "; ";
			moves++;
			cout << *this;
			cout << xPlays << endl;
			if (done() == false) {
				curPlayer = oPlay;
			}
		}
		else if (curPlayer == oPlay) {
			vec[size * y + x] = "O";
			oPlays += to_string(x);
			oPlays += ", ";
			oPlays += to_string(y);
			oPlays += "; ";
			moves++;
			cout << *this;
			cout << oPlays << endl;
			if (done() == false) {
				curPlayer = xPlay;
			}
		}

		if (moves == 9) {
			movesleft = false;
		}
		cout << endl;
		return (int)returns::SUCCESS;
	}
	return 0;
}

int TicTacToeGame::play() {
	print();
	while (done() == false && draw() == false && promptreturn != (int)returns::QUIT) {
		turn();
		done();
		draw();
	}
	if (done() == true) {
		cout << curPlayer << " has won the game!" << endl;
		return (int)returns::SUCCESS;
	}
	if (draw() == true) {
		cout << moves << " turns were taken, resulting in a draw." << endl;
		return (int)returns::DRAW;
	}
	if (promptreturn == (int)returns::QUIT) {
		cout << moves << " turns were taken before the user quit." << endl;
		return (int)returns::QUIT;
	}
	return 0;
}

void TicTacToeGame::print() {
	cout << *this;
}

ostream& operator<<(ostream& o, const TicTacToeGame& t) {
	cout << endl;
	for (int i = t.size - 1; i >= 0; --i) {
		cout << i << setw((int) t.longestPiece + 1);
		for (int j = 0; j < t.size; ++j) {
			string display = t.vec[(int) t.size * i + j];
			cout << display << setw((int) t.longestPiece + 1);
		}
		cout << setw(1) << endl;
	}
	cout << "  ";
	for (int i = 0; i < t.size; i++) {
		cout << i << setw((int) t.longestPiece + 1);
	}
	cout << endl;
	return o;
}

ostream& operator<<(ostream& o, const GomokuGame& g) {
	cout << endl;
	for (int i = g.size; i > 0; --i) {
		cout << i << setw((int)g.longestPiece + 1);
		for (int j = 0; j < g.size; ++j) {
			string display = g.vec[(int)g.size * (i - 1) + j];
			cout << display << setw((int)g.longestPiece + 1);
		}
		cout << setw(1) << endl;
	}

	cout << "X  ";
	for (int i = 0; i < g.size; i++) {
		cout << i + 1<< setw((int)g.longestPiece + 1);
	}
	cout << endl;
	return o;
}


GomokuGame::GomokuGame() {
	size = 19;
	for (int i = 0; i < size * size; ++i) { //populates the vector with empty game pieces
		vec.push_back(" ");
	}
	longestPiece = 2;
}


GomokuGame::~GomokuGame() {
}


bool GomokuGame::done() {
	return doneHelper(vec, size);
}

bool GomokuGame::doneHelper(vector<string> v, int size){
	inARow = 1;
	for (int i = 0; i < size * size; ++i) {
		while (i < size * size && v[i] == " ") {
			i++;
		}
		inARow = 1;
		rowHelper(inARow);
		while (i < size * size && rowHelper(inARow) == false && v[i] != " ") {
				if (i < hiBound && rowHelper(inARow) == false) {
					rowHelper(inARow);
					for (int j = 1; j < 5; ++j) {
						if (v[i] == v[i + (j * size)]) {
							inARow++;
						}
						else {
							inARow = 1;
							j = 5;
						}
					}
					if ((i % size) < rightBound && rowHelper(inARow) == false) {
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i + (j * 20)]) { //checks right diagonal
								inARow++;

							}
							else {
								inARow = 1;
								j = 5;
							}
						}
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i + j]) { //checks right horizontal
								inARow++;

							}
							else {
								inARow = 1;
								j = 5;
							}
						}
					}
					if ((i % size) > leftBound && rowHelper(inARow) == false) {
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i + (j * 18)]) { //checks up vertical
								inARow++;
							}
							else {
								inARow = 1;
								j = 5;
							}
						}
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i - j]) { //checks left horizontal
								inARow++;
							}
							else {
								inARow = 1;
								j = 5;
							}
						}
					}

				} 

				if (i > lowBound && rowHelper(inARow) == false) {
					rowHelper(inARow);
					for (int j = 1; j < 5; ++j) {
						if (v[i] == v[i - (j * size)]) { //checks down vertical
							inARow++;
						}
						else {
							inARow = 1;
							j = 5;
						}
					}
					if (i % size < rightBound && rowHelper(inARow) == false) {
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i - (j * 18)]) { //checks left diagonal
								inARow++;
							}
							else {
								inARow = 1;
								j = 5;
							}
						}
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i + j]) { //checks right horizontal
								inARow++;
							}
							else {
								inARow = 1;
								j = 5;
							}
						}

					}
					if (i % size > leftBound && rowHelper(inARow) == false) {
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i - j]) { //checks left horizontal
								inARow++;
							}
							else {
								inARow = 1;
								j = 5;
							}
						}
						rowHelper(inARow);
						for (int j = 1; j < 5; ++j) {
							if (v[i] == v[i - (j * 20)]) { //checks left diagonal
								inARow++;
							}
							else {
								inARow = 1;
								j = 5;
							}
						}
					}

				}

				if (rowHelper(inARow) == true) {
					return true;
				}
			//}
			i++;
		}
		if (rowHelper(inARow) == true) {
			return true;
		}

		inARow = 1;
	}
	if (movesleft == false) {
		return true;
	}

	return false;
}

bool GomokuGame::rowHelper(int iar) {
	if (iar == 5) {
		rowFound = true;
		return true;
	}
	iar = 1;
	return false;
}

bool GomokuGame::draw() {
	vector<string> checkB = vec;
	vector<string> checkW = vec;
	for (int i = 0; i < size * size; ++i) {
		if (checkB[i] != "W") {
			checkB[i] = "B";
		}
	}
	bool bDone = doneHelper(checkB, size); //checks if Player B can still win
	for (int i = 0; i < size * size; ++i) {
		if (checkW[i] != "B") {
			checkW[i] = "W";
		}
	}
	bool wDone = doneHelper(checkW, size); //checks if Player W can still win

	if ((bDone == false) && (wDone == false)) {
		return true;
	}

	return false;
}


int GomokuGame::turn() {
	cout << endl;
	cout << curPlayer << ", it's your turn!" << endl;
	prompt(x, y);
	if (promptreturn == (int)returns::QUIT) {
		return (int)returns::QUIT;
	}
	if (promptreturn == (int)returns::SUCCESS) {
		if (curPlayer.compare(xPlay) == 0) {
			vec[size * (y - 1) + x - 1] = "B";
			xPlays += to_string(x);
			xPlays += ", ";
			xPlays += to_string(y);
			xPlays += "; ";
			moves++;
			print();
			cout << xPlays << endl;
			if (done() == false) {
				curPlayer = oPlay;
			}
		}
		else if (curPlayer.compare(oPlay) == 0) {
			vec[size * (y - 1) + x - 1] = "W";
			oPlays += to_string(x);
			oPlays += ", ";
			oPlays += to_string(y);
			oPlays += "; ";
			moves++;
			print();
			cout << oPlays << endl;
			if (done() == false) {
				curPlayer = xPlay;
			}
		}
		if (moves == 361) {
			movesleft = false;
		}

		cout << endl;
		return (int)returns::SUCCESS;
	}
	return 0;
}

int GomokuGame::play() {
	print();
	while (done() == false && draw() == false && promptreturn != (int)returns::QUIT) {
		turn();
		done();
		draw();
	}
	if (done() == true) {
		cout << curPlayer << " has won the game!" << endl;
		return (int)returns::SUCCESS;
	}
	if (draw() == true) {
		print();
		cout << moves << " turns were taken, resulting in a draw." << endl;
		return (int)returns::DRAW;
	}
	if (promptreturn == (int)returns::QUIT) {
		print();
		cout << moves << " turns were taken before the user quit." << endl;
		return (int)returns::QUIT;
	}
	return 0;
}

void GomokuGame::print() {
	cout << *this;
}
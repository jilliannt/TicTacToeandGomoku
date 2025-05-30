#pragma once

/*
* Author: Jillian Tarlowe
* Purpose: This file declares functions for the game
*/
#include <vector>
#include <string>

using namespace std;

class GameBase {
protected:
	unsigned int size = 0;
	vector<string> vec;
	unsigned int longestPiece = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	bool movesleft = true;
	int moves = 0;
	unsigned int promptreturn = 0;
public:
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int prompt(unsigned int& x, unsigned int& y);
	virtual int turn() = 0;
	virtual int play() = 0;
	static GameBase* objectConstruct(int, char*[]);
};


class TicTacToeGame : public GameBase {
	friend ostream& operator<< (ostream& o, const TicTacToeGame& t);
private:
	string xPlay = "Player X";
	string xPlays = "Player X:";
	string oPlay = "Player O";
	string oPlays = "Player O:";
	string curPlayer = xPlay;
	enum struct tttindex { BOTLEFT = 6, BOTMID, BOTRIGHT, MIDLEFT, MID, MIDRIGHT, TOPLEFT, TOPMID, TOPRIGHT };
public:
	TicTacToeGame();
	~TicTacToeGame();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual int play();
	virtual void print();
};

ostream& operator<< (ostream& o, const TicTacToeGame& t);

class GomokuGame : public GameBase {
	friend ostream& operator<< (ostream& o, const GomokuGame& g);
private:
	string xPlay = "Player B";
	string xPlays = "Player B:";
	string oPlay = "Player W";
	string oPlays = "Player W:";
	string curPlayer = xPlay;
	int leftBound = 3;
	int rightBound = 15;
	int lowBound = 75;
	int hiBound = 285;
	int inARow = 1;
	bool rowFound = false;
public:
	GomokuGame();
	~GomokuGame();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual int play();
	virtual void print();
	virtual bool GomokuGame::doneHelper(vector<string> vec, int size);
	virtual bool GomokuGame::rowHelper(int iar);
};

ostream& operator<< (ostream& o, const GomokuGame& g);
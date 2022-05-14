#pragma once
#include "Const.h"
#include "GameObject.h"
#include "Error.h"
#include <algorithm>

class Board
{
	char board[terminal_Size_X][terminal_Size_Y];
	int BoardRows;  // Log size of Board
	int BoardCols;

	GameObject legendPos;
	vector<GameObject> ghostsStartPos;
	int ghostNum;
	GameObject playerStartPos;
	vector<GameObject> SecretPathWays;

	int maxFood = 0;

	void ClearLegendArea();

public:
	
	Board(string fileName);
	Board();

	void printBoard();

	// GETTERS:

	char** getBoard();

	char getChar(int i, int j);
	int getBoardRows();
	int getBoardCols();
	GameObject getLegendPos();
	vector<GameObject> getGhostsStartPos();
	int getGhostNum();
	GameObject getPlayerStartPos();
	vector<GameObject> getSecretPathWays();
	int getMaxFood();
	bool checkBlankSpaceForTunnel(int i, int j);
	// SETTER:

	void setBoard(GameObject pos, char ch);
};


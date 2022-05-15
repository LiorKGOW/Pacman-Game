/*----------------------------------------------------------------------------------------------*/
/* Game is the Main Object that controls the game of Pacman.
*/
#pragma once
#include "Player.h"
#include "GameObject.h"
#include "utils.h"
#include "Ghost_Expert.h"
#include "Ghost_Intermediate.h"
#include "Ghost_Novice.h"
#include "Const.h"
#include "Fruit.h"
#include "Board.h"
#include "Error.h"

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class Game {

protected:
	Board* board2;
	vector<string> levelNames;

	char board[terminal_Size_Y][terminal_Size_X] = {};

	char difficultyLevel = BEST;  // if difficultyLevel not chosen, the default is BEST

	bool saveMode;
	std::fstream steps;
	std::fstream result;

public:
	Game(bool _saveMode = NORMAL) {  

		saveMode = _saveMode;
		difficultyLevel = BEST;
	}

	bool withColor = false;  // Is used to determine whether or not the game would be presented with or without colors.
	enum State { WON, LOST, PAUSE };

	void init();  
	void getLevels();
	void printMenu(char& choice);
	void instructions();
	bool startGame(Player& player);  

	void printBoard2();
	void printStats(int lives, int points, int food);
	bool printMessage(State state);

	void movePlayer(Player& player, char ch, char& temp);  
	void moveGhosts(vector<Ghost*>& ghosts, bool& moveTurn, GameObject pacmanPos);  
	void moveFruit(Fruit& fruit, int& moveTurn); 

	bool checkCollision(Player player, vector<Ghost*> ghosts);
	void respawn(Player& player, vector<Ghost*>& ghosts);  

	void findFruitSpawnPoint(Fruit& fruit, Player player, vector<Ghost*> ghosts);  
	void checkFruitCollision(Player& player, vector<Ghost*> ghosts, Fruit& fruit);  

	char getDifficulty() const;
	void setDifficulty(char diff);

	// Save
	string fileNameSteps(string fileName);
	string fileNameResult(string fileName);
};
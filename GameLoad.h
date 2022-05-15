#pragma once
#include "Game.h"

class GameLoad : public Game
{
private:

	bool silentMode;
	bool testPassed;

	std::fstream expectedResult;
	std::fstream currentSteps;

public:

	GameLoad(bool _silentMode = NORMAL, bool _testPassed = true) : Game() {
		
		silentMode = _silentMode;
		testPassed = _testPassed;
	}
	 
	void init(); 
	bool startGame(Player& player);  

	void movePlayer(Player& player, char ch, char& temp); 
	void moveFruit(Fruit& fruit, int& moveTurn, char fDir);
	void moveGhosts(vector<Ghost*>& ghosts, bool& moveTurn, vector<char> ghostDirs);

	void respawn(Player& player, vector<Ghost*>& ghosts);
};
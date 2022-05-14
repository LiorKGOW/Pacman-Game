/*----------------------------------------------------------------------------------------------*/
/* Represents Pacman in the game
*  Inherits from gameObject
*/
#pragma once
#include "GameObject.h"
#include "utils.h"
#include "Const.h"

class Player : public GameObject {

private:
	int Lives;
	int Points;
	char direction;
	int Food;

public:
	Player(int x = 0, int y = 0, int points = 0, int lives = Starting_Lives, char dir = STAY, int Food = 0) : GameObject(x, y) { direction = dir; Points = points; Lives = lives; this->Food = Food; };

	char getDirection() const;
	void setDirection(char dir);
	bool checkLegalMove(char direction, char board[][terminal_Size_X]);
	int getLives() const;
	void setLives(int newLives);
	int getPoints() const;
	void addAPoint();
	int getFood() const;
	void addAFood();
	void zeroFood();

	void move(char dir, char board[][terminal_Size_X], bool withColor, vector<GameObject> secretPaths, bool silentMode = NORMAL);
	void draw();
	void Delete();
	GameObject getPosition() const;
};

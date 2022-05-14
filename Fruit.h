/*----------------------------------------------------------------------------------------------*/
/* Represents a Fruit in the game
*  Inherits from GameObject
*/
#pragma once
#include "GameObject.h"
#include "Const.h"
#include "utils.h"
#include <time.h>
#include "Board.h"
class Fruit : public GameObject
{
private:

	int value;
	char direction;
	int steps;
	bool alive;
	
public:

	Fruit(int x, int y, bool _alive = DEAD, char dir = STAY, int _steps = Max_Fruit_Steps) : GameObject(x, y) {

		/* initialize random seed: */
		srand(time(NULL));

		value = rand() % 5 + 5; // Generate a number between 5 to 9

		direction = dir;

		steps = _steps;

		alive = _alive;
	}

	void move(char board[terminal_Size_Y][terminal_Size_X]);
	bool checkLegalMove(char direction, char board[terminal_Size_Y][terminal_Size_X]);
	void draw();
	void Delete(char board[terminal_Size_Y][terminal_Size_X], bool silentMode = false);

	// GETTERS:

	int getValue() const;
	char getDirection() const;
	int getSteps() const;
	bool getAlive() const;

	// SETTERS:

	void setValue();
	void setSteps(int newSteps);
	void setAlive(bool newState, char board[][terminal_Size_X], bool silentMode = false);
};
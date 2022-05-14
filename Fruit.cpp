#include "Fruit.h"


/*----------------------------------------------------------------------------------------------*/
/* Function controls Fruit movement
*  Generates a random direction and sets the Fruit
*  Location based on that direction UP up 'd' right etc..
*/
void Fruit:: move(char board[terminal_Size_Y][terminal_Size_X]) {

	Delete(board);

	char directions[] = { UP,DOWN , LEFT , RIGHT };
	int randIndex = rand() % 4; // Generate a number between 0 to 3

	char dir = directions[randIndex];

	if (checkLegalMove(dir, board)) {

		if (dir == UP)
		{
			setY(getY() - 1);
		}
		else if (dir == DOWN) {
			setY(getY() + 1);
		}
		else if (dir == RIGHT) {
			setX(getX() + 1);
		}
		else if (dir == LEFT) {
			setX(getX() - 1);
		}
		this->direction = dir;
		steps--;
	}

	draw();

	if (steps == 0) {
	
		Delete(board);

		setAlive(DEAD, board);
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Function takes current coordinates of Fruit and direction and returns if it's valid
*/
bool Fruit::checkLegalMove(char direction, char board[terminal_Size_Y][terminal_Size_X]) {

	int newX = this->getX();
	int newY = this->getY();

	if (direction == UP)
	{
		newY--;
	}
	else if (direction == DOWN)
	{
		newY++;
	}
	else if (direction == RIGHT)
	{
		newX++;
	}
	else if (direction == LEFT)
	{
		newX--;
	}

	if (board[newY][newX] == ' ' || board[newY][newX] == FOOD)

		return true;

	else
		return false;
}

/*----------------------------------------------------------------------------------------------*/
/* Function draws the Fruit on the screen
*  goes to the Fruit's coordinates and draws it
*/
void Fruit::draw() {

	gotoxy(getX(), getY());
	cout << value;
}

/*----------------------------------------------------------------------------------------------*/
/* Hides the Fruit from the User
*/
void Fruit::Delete(char board[][terminal_Size_X], bool silentMode) {

	if (!silentMode) {

		setTextColor(Color::LIGHTGREY);
		gotoxy(getX(), getY());
		cout << board[getY()][getX()];
	}
}

/*----------------------------------------------------------------------------------------------*
* GETTERS:
*----------------------------------------------------------------------------------------------*/
/* Value GETTER
*/
int Fruit:: getValue() const {

	return value;
}

/*----------------------------------------------------------------------------------------------*/
/* Char Direction GETTER
*/
char Fruit::getDirection() const {

	return direction;
}

/*----------------------------------------------------------------------------------------------*/
/* Int steps GETTER
*/
int Fruit::getSteps() const {

	return steps;
}

/*----------------------------------------------------------------------------------------------*/
/* Boolean alive GETTER
*/
bool Fruit::getAlive() const {

	return alive;
}

/*----------------------------------------------------------------------------------------------*
* SETTERS:
*----------------------------------------------------------------------------------------------*/
/* Value SETTER
*/
void Fruit::setValue() {

	/* initialize random seed: */
	srand(time(NULL));

	value = rand() % 5 + 5; // Generate a number between 5 to 9
}

/*----------------------------------------------------------------------------------------------*/
/* steps SETTER
*/
void Fruit::setSteps(int newSteps) {

	steps = newSteps;
}

/*----------------------------------------------------------------------------------------------*/
/* Alive SETTER
*/
void Fruit::setAlive(bool newState,char board[][terminal_Size_X], bool silentMode) {

	alive = newState;

	if (alive) {
		
		setValue();
		steps = Max_Fruit_Steps;
	}
	else {
		this->Delete(board, silentMode);
	}

}
#include "Player.h"

/*----------------------------------------------------------------------------------------------*/
/* Char Direction GETTER
*/
char Player:: getDirection() const {

	return this->direction;
}

/*----------------------------------------------------------------------------------------------*/
/* Char Direction SETTER
*  If direction is not a valid choice {STAY,LEFT,RIGHT,DOWN,UP} IGNORE it
*/
void Player::setDirection(char dir) {

	dir = tolower(dir);

	if (dir != STAY && dir != LEFT && dir != RIGHT && dir != DOWN && dir != UP) {

		// Ignore 
	}
	else
		this->direction = dir;
}

/*----------------------------------------------------------------------------------------------*/
/* Function takes current coordinates of player and direction and returns if it's valid 
*/
bool Player::checkLegalMove(char direction, char board[][terminal_Size_X]) {

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

	if (board[newY][newX] == ' ' || board[newY][newX] == FOOD) {

		if (board[newY][newX] == FOOD) {

			addAFood();
		}
		return true;
	}
	else
		return false;
}

/*----------------------------------------------------------------------------------------------*/
/* Moves the player across the board 
*/
void Player::move(char dir, char board[][terminal_Size_X], bool withColor,vector<GameObject> secretPaths, bool silentMode) {

	if (!silentMode) {

		Delete();
	}

	bool secretMove = false;
	for (auto secPos : secretPaths)
	{
		if (secretMove)
		{
			break;
		}
		if (getX() == secPos.getX() && getY() == secPos.getY()) {

			if ((dir == RIGHT || dir == LEFT) && (board[getY()][getX()+1] != '#'))
			{
				for (int i = 0; i < secretPaths.size(); i++)
				{
					if (secretPaths[i].getY() == secPos.getY() && secretPaths[i].getX() != secPos.getX())
					{
						setX(secretPaths[i].getX());
						setY(secretPaths[i].getY());
						secretMove = true;
						if (board[getY()][getX()] == FOOD)
						{
							board[getY()][getX()] = ' ';
							addAFood();
						}
						break;
					}
				}
			}
			else if ((dir == UP || dir == DOWN) && (board[getY() + 1][getX()] != '#')){ // if dir == DOWN || dir == UP
				for (int i = 0; i < secretPaths.size(); i++)
				{
					if (secretPaths[i].getX() == secPos.getX() && secretPaths[i].getY() != secPos.getY())
					{
						setX(secretPaths[i].getX());
						setY(secretPaths[i].getY());
						secretMove = true;
						if (board[getY()][getX()] == FOOD)
						{
							board[getY()][getX()] = ' ';
							addAFood();
						}
						break;
					}
				}
			}
		}
	}

	if (checkLegalMove(dir, board)) {

		board[getY()][getX()] = ' ';

		if (dir == UP)
		{
			this->setY(getY() - 1);
		}
		else if (dir == DOWN)
		{
			this->setY(getY() + 1);
		}
		else if (dir == RIGHT) 
		{
			this->setX(getX() + 1);
		}
		else if (dir == LEFT) 
		{
			this->setX(getX() - 1);
		}
	}
	else 
		this->setDirection(STAY);

	if (!silentMode) {

		if (withColor)
			setTextColor(Color::YELLOW);

		draw();
	}
}

/*----------------------------------------------------------------------------------------------*/

GameObject Player::getPosition() const{
	
	return GameObject(getX(), getY());
}

/*----------------------------------------------------------------------------------------------*/
/* Function draws the '@' (pacman) in the terminal using the objects cooridinates
*/
void Player::draw() {

	gotoxy(getX(), getY());
	cout << '@';
}

/*----------------------------------------------------------------------------------------------*/
/* Hides the player from the User
*/
void Player:: Delete() {

	gotoxy(getX(), getY());
	cout << ' ';
}

/*----------------------------------------------------------------------------------------------*/
/* GETTER for player lives
*/
int Player::getLives() const {
	return this->Lives;
}

/*----------------------------------------------------------------------------------------------*/
/* SETTER for player lives
*/
void Player::setLives(int newLives) {
	this->Lives = newLives;
}

/*----------------------------------------------------------------------------------------------*/
/* GETTER for player points
*/
int Player::getPoints() const {
	return this->Points;
}

/*----------------------------------------------------------------------------------------------*/
/* SETTER for player points
*/
void Player::addAPoint() {
	this->Points = this->getPoints() + 1;
}

/*----------------------------------------------------------------------------------------------*/
/* GETTER for player Food
*/
int Player:: getFood() const {

	return this->Food;
}

/*----------------------------------------------------------------------------------------------*/
/* SETTER for player Food
*/
void Player:: addAFood() {

	this->Food = this->Food + 1;
	addAPoint();
}

/*----------------------------------------------------------------------------------------------*/

void Player:: zeroFood() {

	this->Food = 0;
}

/*----------------------------------------------------------------------------------------------*/
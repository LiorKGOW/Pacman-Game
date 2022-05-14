#include "Board.h"

/*----------------------------------------------------------------------------------------------*/

void Board:: ClearLegendArea() {

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 20; j++) {

			board[i + legendPos.getY()][j + legendPos.getX()] = ' ';
		}
	}
}

/*----------------------------------------------------------------------------------------------*/

Board::Board(string fileName) {

	bool only1Pacman = false;
	bool moreThan1Pacman = false;
	
	// Ghost vector.size

	bool only1Legend = false;
	bool moreThan1Legend = false;

	// ilegal tunnels -> do not check
	// a piece missing in the board -> function to verify that the board is a fixed shape.

	// ilegal board, continue to next board + proper message
	// ilegal board, with a fixable problem, do you wish to continue to play? bugs could be found

	// ilegal legend pos

	ifstream myFile(fileName);

	string line;
	int i = 0;
	int j = 0;

	while (getline(myFile, line)) {

		j = 0;
		
		for (auto c : line) {

			if (c == ' ') {

				c = FOOD;
				maxFood++;
			}
			else if (c == '%') {

				c = ' ';
			}
			else if (c == '@') { 

				if (only1Pacman) {

					moreThan1Pacman = true;
				}
				else {

					only1Pacman = true;
				}

				if (moreThan1Pacman) {  // illegal board, more then 1 Pacman

					throw PacmanError();
				}
				else {

					playerStartPos = GameObject(j, i);
					c = ' ';
				}
			}
			else if (c == '$') {

				ghostsStartPos.push_back(GameObject(j, i));
				c = ' ';
			}
			else if (c == '&') { // LEGENDDDDD

				if (only1Legend) {

					moreThan1Legend = true;
				}
				else {

					only1Legend = true;
				}

				if (moreThan1Legend) {  // illegal board, more then 1 Legend

					throw LegendError();
				}
				else {

					legendPos = GameObject(j, i);
					c = ' ';

					ClearLegendArea();
				}
			}

			// else , c == '#' => Do nothing

			board[i][j] = c;
			
			j++;
		}

		BoardCols = std::max((int)line.length(), BoardCols);

		// cout << line <<endl;
		i++;
	}

	// Legal Board Checks:

	if (!only1Pacman) {

		throw Pacman0Error();
	}

	if (!only1Legend) {

		throw Legend0Error();
	}

	if (ghostsStartPos.size() > 4) {

		throw GhostError();
	}

	// Tunnel / Board Checks??

	// Board was Legal, continue KENNYYY

	BoardRows = i;

	myFile.close();


	//This loops over the board and sends every ' ' character to be checked if
	//it's actually a secret tunnel, if it is push into vector of SecretPathWays
	for (int i = 0; i < BoardRows; i++)
	{
		for (int j = 0; j < BoardCols; j++)
		{
			if (board[i][j] == ' ' || board[i][j] == FOOD || board[i][j]== '%')
			{
				if (checkBlankSpaceForTunnel(i, j))
				{
					this->SecretPathWays.push_back(GameObject(j, i));
				}
			}
		}
	}

	//This loops over the secret pathways and removes the food from them
	//also reduces the maxfood as needed
	for (int i = 0; i < SecretPathWays.size(); i++)
	{
		if (board[SecretPathWays[i].getY()][SecretPathWays[i].getX()] == FOOD)
		{
			board[SecretPathWays[i].getY()][SecretPathWays[i].getX()] = ' ';
			maxFood--;
		}
	}
}

/*----------------------------------------------------------------------------------------------*/

char Board::getChar(int i, int j) {

	return board[i][j];
}

/*----------------------------------------------------------------------------------------------*/

bool Board::checkBlankSpaceForTunnel(int i, int j) {

	if (j == 0 && i == 0)
	{
		return false; // no situation where _# is a tunnel
	}				  //                    #
	if ( (board[i][j + 1] == '#' && board[i][j - 1] == '#')) { // if situation like #_#
		if (i == 0 || i == BoardRows - 1) // if it's the first line or last line and no legend interruption
		{
			return true;
		}
		if (board[i - 1][j] == '\0' || board[i + 1][j] == '\0') { //if situation like #_# and the above is blank
			return true;
		}
	}
	else if ((i > 0 && i < terminal_Size_Y - 1) && (board[i + 1][j] == '#' || board[i - 1][j] == '#')) {
		if (j == 0 || i == BoardRows - 1) // if it's the first line or last line and no legend interruption
		{
			return true;
		}
		if (board[i][j - 1] == '\0' || board[i][j + 1] == '\0') { //if situation like #_# and the above is blank
			return true;
		}
	}
	return false;
}

/*----------------------------------------------------------------------------------------------*/

void Board::printBoard() {

	for (int row = 0; row < BoardRows; row++) {

		for (int col = 0; col < BoardCols; col++) {

			cout << board[row][col];
		}

		cout << endl;
	}
}

/*----------------------------------------------------------------------------------------------*/
// GETTERS:
/*----------------------------------------------------------------------------------------------*/

char** Board:: getBoard() {

	return (char**)board;
}

/*----------------------------------------------------------------------------------------------*/

int Board:: getBoardRows() {

	return BoardRows;
}

/*----------------------------------------------------------------------------------------------*/

int Board:: getBoardCols() {

	return BoardCols;
}

/*----------------------------------------------------------------------------------------------*/

int Board:: getGhostNum() {

	return ghostsStartPos.size();
}

/*----------------------------------------------------------------------------------------------*/

GameObject Board::getLegendPos() {

	GameObject ret = legendPos;
	return ret;
}

/*----------------------------------------------------------------------------------------------*/

vector<GameObject> Board::getGhostsStartPos() {

	vector <GameObject> ret = ghostsStartPos;
	return ret;
}

/*----------------------------------------------------------------------------------------------*/

GameObject Board:: getPlayerStartPos() {

	GameObject ret = playerStartPos;
	return ret;
}

/*----------------------------------------------------------------------------------------------*/

vector<GameObject> Board:: getSecretPathWays() {

	vector <GameObject> ret = SecretPathWays;
	return ret;
}

/*----------------------------------------------------------------------------------------------*/

int Board::getMaxFood()
{
	return maxFood;
}

/*----------------------------------------------------------------------------------------------*/
// SETTER:
/*----------------------------------------------------------------------------------------------*/

void Board::setBoard(GameObject pos, char ch) {

	board[pos.getY()][pos.getX()] = ch;
}

/*----------------------------------------------------------------------------------------------*/

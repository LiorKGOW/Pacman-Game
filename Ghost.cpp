#include "Ghost.h"

/*----------------------------------------------------------------------------------------------*/
/* Function controls Ghosts movement
*  Diverts the movement to the coresponding function based on the difficulty chosen by the player
*  Pure virtual function, which is implemented in the Derived classes
*/
//virtual void Ghost::move(char board[][terminal_Size_X], GameObject pacmanPos, vector<Ghost> ghosts) {

	//Delete(board);
	//char direction = STAY;

	//char directions[] = { UP,DOWN , LEFT , RIGHT };
	//int randIndex;

	//int playDumb;

	//if (difficulty == BEST)  // BEST
	//{
	//	direction = aStar(board, pacmanPos, ghosts);

	//	this->dir = direction;
	//}
	//else if (difficulty == GOOD) {
	//	//moveMedium

	//	// generate a random number between 0 and 9 and if it a 7 then move to a random direction for 5 moves.
	//	if (moveCount < 20) { 

	//		direction = this->dir;
	//		moveCount++;
	//	}
	//	else {
	//		playDumb = rand() % Medium_Dumb_Ghost_Rate;

	//		if (playDumb == 0) {

	//			randIndex = rand() % 4; // Generate a number between 0 to 3

	//			this->dir = directions[randIndex];
	//			moveCount = 15;

	//			direction = this->dir;
	//		}
	//		else
	//			direction = aStar(board, pacmanPos, ghosts);

	//		this->dir = direction;
	//	}
	//}
	//else {  // C NOVICE
	//	//moveRandomly

	//	if (moveCount < 20)

	//		moveCount++;

	//	else {
	//		randIndex = rand() % 4; // Generate a number between 0 to 3

	//		this->dir = directions[randIndex];
	//		moveCount = 0;
	//	}

	//	direction = this->dir;
	//}

	//move(board, direction, ghosts);

	//draw();
//}

/*----------------------------------------------------------------------------------------------*/
/* Function implements movement using the A* algorithm
*  Take the board and the position of the pacman
*  calculates a lovely path to the postion given and returns the direction as a char
*/
char Ghost::aStar(char board[][terminal_Size_X], GameObject end,vector<Ghost*> ghosts) {


	int breakOutOfLoop = terminal_Size_X * 2; // in case player out of bounds limit to how many times loop runs
	int breaker = 0; // init breaker for loop

	int startEndDistance = pow((getX() - end.getX()), 2) + pow((getY() - end.getY()), 2);

	PathNode *startNode = new PathNode(getPosition(), 0, startEndDistance);  // in the ctor of PathNode, the default values of Parent == nullptr.

	PathNode endNode(end, startEndDistance, 0);  // in the ctor of PathNode, the default values of Parent == nullptr.

	// Initialize both Open and Closed Lists:
	vector<PathNode*> openList;
	vector<PathNode*> closedList;
	vector <PathNode*> children;

	// Add the StartNode:
	openList.push_back(startNode);

	// Loop until you find the end:
	while (openList.size() > 0) {

		breaker++;
		if (breaker == breakOutOfLoop) {

			//clean memory allocations

			while (!openList.empty()) {
				PathNode* node = openList.back();
				openList.pop_back();
				delete node;
			}
			while (!closedList.empty()) {
				PathNode* node = closedList.back();
				closedList.pop_back();
				delete node;
			}

			return moveApproc(end, board, ghosts);
		}
			
		// Get the current Node.
		PathNode* currentNode = openList[0];  // Default copy ctor.

		int index = 0;

		for (int i = 0; i < openList.size(); i++) {

			if ((*openList[i]).getf() < (*currentNode).getf()) {

				index = i;
				currentNode = openList[i];
			}
		}

		// Pop Current off openList, and add to closedList:
		openList.erase(openList.begin() + index);
		closedList.push_back(currentNode);

		// If found the end, return:
		if (*currentNode == endNode) {

			// return direction of the first move of the path:
			PathNode* nextNode = currentNode;
			PathNode* firstMoveNode = nullptr;

			while (*nextNode != *startNode) {

				firstMoveNode = nextNode;
				nextNode = nextNode->getParent();
			}

			if (firstMoveNode == nullptr)  //for the case of same location
				return 's';

			GameObject newPos = firstMoveNode->getPosition();
			GameObject currentPos = (*startNode).getPosition();

			while (!openList.empty()) {
				PathNode* node = openList.back();
				openList.pop_back();
				delete node;
			}
			while (!closedList.empty()) {
				PathNode* node = closedList.back();
				closedList.pop_back();
				delete node;
			}

			if (newPos.getX() - currentPos.getX() == 0 && newPos.getY() - currentPos.getY() == 1) {

					return DOWN;
			}	
			else if (newPos.getX() - currentPos.getX() == 0 && newPos.getY() - currentPos.getY() == -1) {

				return UP;
			}
			else if (newPos.getX() - currentPos.getX() == 1 && newPos.getY() - currentPos.getY() == 0)

				return RIGHT;

			else if (newPos.getX() - currentPos.getX() == -1 && newPos.getY() - currentPos.getY() == 0)

				return LEFT;

			else
				return STAY;
		}


		children.clear();

		// temp is used to generate the children of the currentNode.
		GameObject temp[4];
		temp[0] = GameObject(0, 1);   // Position above currentNode
		temp[1] = GameObject(1, 0);   // Position right of currentNode
		temp[2] = GameObject(0, -1);  // Position left of currentNode
		temp[3] = GameObject(-1, 0);  // Position below currentNode

		for (int i = 0 ; i < 4; i++) {

			// Get Node Position:
			GameObject nodePosition(((*currentNode).getPosition() + temp[i]));

			// Make Sure within Range of board & Not a Wall (walkable terrain):
			if (!checkLegalMove(nodePosition, board, ghosts))

				continue;
			
			PathNode * newNode = new PathNode(nodePosition, 0, 0, currentNode);
			children.push_back(newNode);
		}

		// Loop through Children:

		for (auto& child : children) {

			bool addChild = true;

			// Child is on the closedList:
			for (auto& closedChild : closedList) {

				if (*child == *closedChild) {

					addChild = false;
					continue;
				}
			}

			if (!addChild)  
				continue;

			// Create the G H and F values:
			(*child).setg(((*currentNode).getg() + 1));
			(*child).seth(pow(((*child).getPosition().getX() - endNode.getPosition().getX()), 2) + pow(((*child).getPosition().getY() - endNode.getPosition().getY()), 2));
			(*child).setf((*child).getg() + (*child).geth());

			// Child is already in the openList:
			for (auto& openNode : openList) {

				if (*child == *openNode && (*child).getg() > (*openNode).getg()) {

					addChild = false;

					continue;
				}
			}

			if (!addChild)  continue;

			openList.push_back(child);
		}
	}

	return 's';
}

/*----------------------------------------------------------------------------------------------*/

char Ghost::moveApproc(GameObject end, char board[][terminal_Size_X],vector<Ghost*> ghosts) {

	if (end.getX() > getX() && checkLegalMove(RIGHT, board, ghosts))
	{
		return RIGHT;
	}
	else if (end.getX() < getX() && checkLegalMove(LEFT, board, ghosts)) {
		return LEFT;
	}
	else if (end.getY() < getY() && checkLegalMove(DOWN, board, ghosts)) {
		return DOWN;
	}
	else if (end.getY() > getY() && checkLegalMove(UP, board, ghosts)) {
		return UP;
	}
	else {
		return STAY;
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Function controls Ghosts movement
*  Generates a random direction and sets the Ghosts
*  Location based on that direction UP up 'd' right etc..
*/
void Ghost::move(char board[][terminal_Size_X], char dir, vector<Ghost*> ghosts){

	if (checkLegalMove(dir, board, ghosts)) {

		if (dir == UP)
		{
			this->setY(getY() - 1);
		}
		else if (dir == DOWN) {
			this->setY(getY() + 1);
		}
		else if (dir == RIGHT) {
			this->setX(getX() + 1);
		}
		else if (dir == LEFT) {
			this->setX(getX() - 1);
		}

		this->dir = dir;
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Function draws the ghost on the screen
*  goes to the Ghost's coordinates and draws it
*/
void Ghost::draw() {

	gotoxy(getX(), getY());
	cout << '&';
}

/*----------------------------------------------------------------------------------------------*/
/* Hides the Ghost from the User
*/
void Ghost:: Delete(char board[][terminal_Size_X]) {

	setTextColor(Color::LIGHTGREY);

	gotoxy(getX(), getY());
	cout << board[getY()][getX()];
}

/*----------------------------------------------------------------------------------------------*/
/* Function takes current coordinates of Ghost and direction and returns if it's valid
*/
bool Ghost::checkLegalMove(char direction, char board[][terminal_Size_X],vector<Ghost*> ghosts) {

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

	for (auto g: ghosts)
	{
		if (g->getPosition() == GameObject(newX,newY))
		{
			return false;
		}
	}

	if (board[newY][newX] == ' ' || board[newY][newX] == FOOD)

		return true;

	else
		return false;
}

/*----------------------------------------------------------------------------------------------*/
/* Function takes current position of currentNode, and returns if it's valid
*  This function helps Astar to find the path to the pacman.
*/
bool Ghost::checkLegalMove(GameObject pos, char board[][terminal_Size_X], vector<Ghost*> ghosts) {

	pos.getX();
	pos.getY();

	for (auto g : ghosts)
	{
		if (g->getPosition() == GameObject(pos.getX(), pos.getY()))
		{
			return false;
		}
	}

	if (board[pos.getY()][pos.getX()] == ' ' || board[pos.getY()][pos.getX()] == FOOD)

		return true;

	else
		return false;
}

/*----------------------------------------------------------------------------------------------*/

char Ghost::getDirection() const {

	return this->dir;
}

/*----------------------------------------------------------------------------------------------*/

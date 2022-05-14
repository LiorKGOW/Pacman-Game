#include "Ghost_Novice.h"

void Ghost_Novice::move(char board[][terminal_Size_X], GameObject pacmanPos, vector<Ghost*> ghosts) {

	Delete(board);
	char direction = STAY;

	char directions[] = { UP,DOWN , LEFT , RIGHT };
	int randIndex;

	int playDumb;

	//moveRandomly:

	if (moveCount < 20)

		moveCount++;

	else {
		randIndex = rand() % 4; // Generate a number between 0 to 3

		this->dir = directions[randIndex];
		moveCount = 0;
	}

	direction = this->dir;

	Ghost::move(board, direction, ghosts);

	draw();
}

/*----------------------------------------------------------------------------------------------*/

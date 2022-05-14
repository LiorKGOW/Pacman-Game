#include "Ghost_Intermediate.h"

void Ghost_Intermediate::move(char board[][terminal_Size_X], GameObject pacmanPos, vector<Ghost*> ghosts) {

	Delete(board);
	char direction = STAY;

	char directions[] = { UP,DOWN , LEFT , RIGHT };
	int randIndex;

	int playDumb;

	// generate a random number between 0 and 9 and if it a 7 then move to a random direction for 5 moves.
	if (moveCount < 20) {

		direction = this->dir;
		moveCount++;
	}
	else {

		playDumb = rand() % Medium_Dumb_Ghost_Rate;

		if (playDumb == 0) {

			randIndex = rand() % 4; // Generate a number between 0 to 3

			this->dir = directions[randIndex];
			moveCount = 15;

			direction = this->dir;
		}
		else
			direction = aStar(board, pacmanPos, ghosts);

		this->dir = direction;
	}

	// move & draw:

	Ghost::move(board, direction, ghosts);

	draw();
} 

/*----------------------------------------------------------------------------------------------*/

#include "Ghost_Expert.h"

void Ghost_Expert::move(char board[][terminal_Size_X], GameObject pacmanPos, vector<Ghost*> ghosts) {

	Delete(board);
	char direction = STAY;

	char directions[] = { UP,DOWN , LEFT , RIGHT };
	int randIndex;

	int playDumb;

	direction = aStar(board, pacmanPos, ghosts);

	this->dir = direction;

	// move & draw:

	Ghost::move(board, direction, ghosts);

	draw();
}

/*----------------------------------------------------------------------------------------------*/

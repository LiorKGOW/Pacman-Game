#include "utils.h"
#include <conio.h>
#include "Game.h"
#include "Board.h"
#include "Const.h"
#include "GameLoad.h"

/*----------------------------------------------------------------------------------------------*/
/* This Program is a Game called Pacman
*  
*  Guy Sternshos, ID: 318423415  
*  Lior Keren,    ID: 208547992
* 
* NOTICE! 
* - Please make sure that your compiler level fits C++ 17 and above!
* - Be sure to include .screen files that you wish to play on in the game's current directory, 
*   in the format described in the format file attached
* 
*/
int main(int argc, char* argv[]) {
	
	if (argc == 1)
	{
		Game game;
		game.init();
	}
	else if (!strcmp(argv[1],"-load")) {

		if (argc == 3)
		{
			if (!strcmp(argv[2], "-silent"))
			{
				GameLoad game(SILENT);
				game.init();
			}
			else {

				cout << "wrong argument provided...\n";
			}
		}
		else {

			GameLoad game(NORMAL);
			game.init();
		}
	}
	else if (!strcmp(argv[1], "-save")) {  // if the user added silent to save mode the program ignores it

		Game game(SAVE);
		game.init();
	}
	else {
		cout << "wrong argument provided...\n";
	}

	return 0;
}

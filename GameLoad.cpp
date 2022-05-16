#include "GameLoad.h"

void GameLoad:: init() {
	
	// get underlying buffer
	std::streambuf* orig_buf = cout.rdbuf();

	if (silentMode) {

		std::cout.setstate(std::ios_base::failbit);

		// set null
		cout.rdbuf(NULL);
	}

	getLevels();

	bool won = true;
	int currentLevel = 0;

	system("cls");

	Player player;

	// Start Game:
	while (currentLevel < levelNames.size() && levelNames.size() > 0) {

		board2 = new Board(levelNames[currentLevel]);

		for (int i = 0; i < terminal_Size_X; i++)
		{
			for (int j = 0; j < terminal_Size_Y; j++)
			{
				board[i][j] = board2->getChar(i, j);
			}
		}

		player.setPosition(board2->getPlayerStartPos());
		player.zeroFood();

		currentSteps.open(fileNameSteps(levelNames[currentLevel]), std::ios::in);
		expectedResult.open(fileNameResult(levelNames[currentLevel]), std::ios::in);

		won = startGame(player);

		delete board2;

		if (won) {

			// Load next Stage

			currentSteps.close();
			expectedResult.close();

			currentLevel++;
		}
		else {  // Lost Game

			currentSteps.close();
			expectedResult.close();

			if (!silentMode) {

				system("cls");

				cout << youLost << endl;
			
				Sleep(2000);
			}

			if (silentMode) {

				system("cls");
			}
			break;
		}
	}

	if (won){

		// Won Game
		if (!silentMode) {

			system("cls");

			cout << congrats << endl;

			Sleep(2000);
		}
	}

	if (silentMode) {

		std::cout.clear();

		// restore buffer
		cout.rdbuf(orig_buf);

		system("cls");

		if (testPassed) {

			cout << "Test Passed" << endl;
		}
		else {

			cout << "Test Failed" << endl;
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Function that runs the actual game loop/logic of the game
*/
bool GameLoad::startGame(Player& player) {

	long int gameLoops = 1;

	if (!silentMode) {

		system("cls");
		printBoard2();
	}

	bool continueGame = false;
	bool MoveGhost = false;
	int MoveFruit = 0;

	bool lostGame = false;
	bool wonLevel = false;

	vector <Ghost*> ghosts;

	if (difficultyLevel == BEST) {

		for (int i = 0; i < board2->getGhostNum(); i++) {

			ghosts.push_back(new Ghost_Expert(board2->getGhostsStartPos()[i]));
		}
	}
	else if (difficultyLevel == GOOD) {

		ghosts.push_back(new Ghost_Expert(board2->getGhostsStartPos()[0]));

		for (int i = 1; i < board2->getGhostNum(); i++) {

			ghosts.push_back(new Ghost_Intermediate(board2->getGhostsStartPos()[i]));
		}
	}
	else {  //difficultyLevel == NOVICE

		ghosts.push_back(new Ghost_Intermediate(board2->getGhostsStartPos()[0]));

		for (int i = 1; i < board2->getGhostNum(); i++) {

			ghosts.push_back(new Ghost_Novice(board2->getGhostsStartPos()[i]));
		}
	}

	Fruit fruit(0, 0);
	if (ghosts.size() > 0)
	{
		fruit.setPosition(ghosts[0]->getPosition());
	}
	else {
		fruit.setPosition(player.getPosition());
	}

	char ch = STAY;
	char temp = STAY;

	char fruitDir = STAY;

	size_t fruitind;
	size_t pacmanind;
	
	vector<size_t> ghostind(ghosts.size());
	vector<char> ghostDirs(ghosts.size());

	do {

		string moves;
		getline(currentSteps, moves);

		pacmanind = moves.find("Pacman");

		ch = moves[pacmanind + 8];

		if (fruit.getAlive()) {

			fruitind = moves.find("Fruit");

			if (fruitind != string::npos) {

				fruitDir = moves[fruitind + 7];
			}
			else {

				fruitDir = STAY;
			}
		}

		for (int i = 0; i < ghosts.size(); i++) {

			ghostind[i] = moves.find("Ghost" + std::to_string(i));
			ghostDirs[i] = moves[ghostind[i] + 8];
		}
		
		if (!silentMode) {

			printStats(player.getLives(), player.getPoints(), player.getFood());
			hideCursor();
		}

		moveFruit(fruit, MoveFruit, fruitDir);
		//write fruit move

		movePlayer(player, ch, ch);
		//write player move to file

		if (!silentMode)
		{
			Sleep(SPEED);

			hideCursor();

			player.draw();
		}

		moveGhosts(ghosts, MoveGhost, ghostDirs);
		//write ghost moves to file

		if(!fruit.getAlive()) {

			if (!silentMode) {

				fruit.Delete(board);
			}

			fruitind = moves.find("Fruit new");

			if (fruitind != string::npos) {

				fruit.setAlive(ALIVE, board, silentMode);

				int tempX, tempY;

				fruitind = moves.find("X:") + 3;
				int psik = moves.find(",");
				tempX = std::stoi(moves.substr(fruitind, psik - fruitind));

				fruitind = moves.find("Y:") + 3;

				tempY = std::stoi(moves.substr(fruitind));

				fruit.setPosition(GameObject(tempX, tempY));
			}		
		}

		if (checkCollision(player, ghosts))
		{
			string resultLine;
			getline(expectedResult, resultLine);

			if (resultLine != ("Pacman died: " + std::to_string(gameLoops))) {   // + '\n'

				testPassed = false;
			}

			if (player.getLives() > 1)
			{
				respawn(player, ghosts);
			}
			else {
				lostGame = true;
			}
		}

		checkFruitCollision(player, ghosts, fruit);

		if (player.getFood() == board2->getMaxFood())
		{
			wonLevel = true;

			string resultLine;
			getline(expectedResult, resultLine);

			if (resultLine != ("Pacman Finished the Screen: " + std::to_string(gameLoops))) {   // + '\n'

				testPassed = false;
			}
		}

		gameLoops++;

	} while (!lostGame && !wonLevel);

	// free ghost memory:

	for (int i = 0; i < ghosts.size(); i++) {

		delete ghosts[i];
	}

	if (lostGame)
		return false;

	return true;
	// go to next screen.......................
}

/*----------------------------------------------------------------------------------------------*/
/* Moves the Pacman
*/
void GameLoad::movePlayer(Player& player, char ch, char& temp) {

	ch = tolower(ch);

	if (ch == UP || ch == DOWN || ch == RIGHT || ch == LEFT)
	{
		temp = ch;
		player.move(ch, board, withColor, board2->getSecretPathWays(), silentMode);
	}
	else if (ch == STAY) {

		temp = ch;
	}
	else {
		player.move(tolower(temp), board, withColor, board2->getSecretPathWays(), silentMode);
	}
}

/*----------------------------------------------------------------------------------------------*/

void GameLoad::moveFruit(Fruit& fruit, int& moveTurn,char fDir) {

	if (!silentMode) {

		fruit.Delete(board);
	}

	if (fruit.getAlive()) {

		// Movement of the Fruit is half of the movement of Ghost
		moveTurn = (moveTurn + 1) % 4;

		if (moveTurn == 1) {

			if (fruit.checkLegalMove(fDir, board)) {

				if (fDir == UP)
				{
					fruit.setY(fruit.getY() - 1);
				}
				else if (fDir == DOWN) {
					fruit.setY(fruit.getY() + 1);
				}
				else if (fDir == RIGHT) {
					fruit.setX(fruit.getX() + 1);
				}
				else if (fDir == LEFT) {
					fruit.setX(fruit.getX() - 1);
				}

				fruit.setSteps(fruit.getSteps() - 1);
			}
		}

		if(fruit.getAlive())
			
			if (!silentMode) {

				fruit.draw();
			}
	}
	else  // fruit is DEAD

		if (!silentMode) {

			fruit.Delete(board);
		}

	if (fruit.getSteps() == 0) {

		if (!silentMode) {

			fruit.Delete(board);
		}

		fruit.setAlive(DEAD, board);
	}
}

/*----------------------------------------------------------------------------------------------*/

void GameLoad::moveGhosts(vector<Ghost*>& ghosts, bool& moveTurn, vector<char> ghostDirs) {

	// Movement of the Ghosts is half of the movement of Pacman
	moveTurn = !moveTurn;

	if (moveTurn) {

		for (int i = 0; i < ghosts.size(); i++) {
			
			if (!silentMode) {

				ghosts[i]->Delete(board);
			}

			char fDir = ghostDirs[i];

			if (ghosts[i]->checkLegalMove(fDir, board, ghosts))
			{
				if (fDir == UP)
				{
					ghosts[i]->setY(ghosts[i]->getY() - 1);
				}
				else if (fDir == DOWN) {
					ghosts[i]->setY(ghosts[i]->getY() + 1);
				}
				else if (fDir == RIGHT) {
					ghosts[i]->setX(ghosts[i]->getX() + 1);
				}
				else if (fDir == LEFT) {
					ghosts[i]->setX(ghosts[i]->getX() - 1);
				}
			}
		}
	}

	Color arr[4] = { Color::RED , Color::MAGENTA, Color::CYAN, Color::BROWN };

	if (!silentMode) {

		for (int i = 0; i < ghosts.size(); i++) {

			if (withColor)
				setTextColor(arr[i]);
			ghosts[i]->draw();
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Returns player and ghosts to their original positions, and substracts 1 point from player's lives \
*/
void GameLoad::respawn(Player& player, vector<Ghost*>& ghosts) {

	player.setLives(player.getLives() - 1); //minus one life

	if (!silentMode) {

		player.Delete();

		for (int i = 0; i < ghosts.size(); i++) {

			ghosts[i]->Delete(board);
		}
	}

	//player starting position
	player.setX(board2->getPlayerStartPos().getX());
	player.setY(board2->getPlayerStartPos().getY());

	//ghosts starting position
	for (int i = 0; i < ghosts.size(); i++) {

		ghosts[i]->setX(board2->getGhostsStartPos()[i].getX());
		ghosts[i]->setY(board2->getGhostsStartPos()[i].getY());
	}
}

/*----------------------------------------------------------------------------------------------*/

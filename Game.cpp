#include "Game.h"

/*----------------------------------------------------------------------------------------------*/
/* First function that is called on the object
*  Basically direct the player to the game/insturctions/exit
*/
void Game::init() {

	getLevels();
	char choice;
	bool singleLevelChosen = false;

	while (true) {

		bool won = true;
		int currentLevel = 0;
		
		printMenu(choice);

		if (choice == '1')
		{
			system("cls");

			if (levelNames.size() == 0) {
				cout << banner;
				cout << "Sorry!\nIt appears there are available .screen files in the current directory.\n";
				cout << "Press any button to go back to main screen\n";
				_getch();
				continue;
			}
			if (!singleLevelChosen)
			{
				levelNames.clear();
				getLevels();
			}
			else {
				singleLevelChosen = false;
			}
		
			Player player;

			// Start Game:
			while (currentLevel < levelNames.size() && levelNames.size() > 0) {

				try {

					board2 = new Board(levelNames[currentLevel]);
				}
				catch (Error& err) {

					string nameOfLevel = levelNames[currentLevel];

					std::size_t slash = nameOfLevel.find_last_of("\\"); // find last slash in file path
					std::size_t dot = nameOfLevel.find_last_of(".screen"); // find where ending .screen

					int a = nameOfLevel.substr(slash + 1).length() - 7; // get substring len - ".screen"
					nameOfLevel = nameOfLevel.substr(slash + 1, a); // file name

					cout << nameOfLevel << endl << err.getMsg() << endl;
					
					cout << "Press any key to continue... " << endl;

					_getch();

					system("cls");

					currentLevel++;
					continue;
				}

				// Else, Board was legal, let's play KENNYYYY

				for (int i = 0; i < terminal_Size_X; i++)
				{
					for (int j = 0; j < terminal_Size_Y; j++)
					{
						board[i][j] = board2->getChar(i, j);
					}
				}

				player.setPosition(board2->getPlayerStartPos());
				player.zeroFood();

				if (saveMode) {

					steps.open(fileNameSteps(levelNames[currentLevel]), std::ios::out | std::ofstream::trunc);
					result.open(fileNameResult(levelNames[currentLevel]), std::ios::out | std::ofstream::trunc);
				}
				won = startGame(player);

				delete board2;

				if (won) {

					// Load next Stage

					currentLevel++;

					if (saveMode) {

						steps.close();
						result.close();
					}
				}
				else {  // Lost

					printMessage(LOST);

					if (saveMode) {

						steps.close();
						result.close();
					}

					break;
				}
			}

			if (won)
				printMessage(WON);
		}
		else if (choice == '2') {
			system("cls");
			char temp;

			setTextColor(Color::LIGHTGREY);
			cout << banner;
			cout << "Hello what difficulty would you like to play?\n\n";
			cout << "Deafult difficulty is BEST\n";
			cout << "a) BEST\n";
			cout << "b) GOOD\n";
			cout << "c) NOVICE\n";

			temp = _getch();

			temp = tolower(temp);
			if (temp == 'a' || temp == 'b' || temp == 'c')
			{
				setDifficulty(temp);
			}
			else {
				cout << "invalid option!" << endl;
				cout << "press any key to return to main menu" << endl;
				_getch();
			}
		}
		else if (choice == '3') {
			system("cls");
			setTextColor(Color::LIGHTGREY);

			cout << banner;
			cout << "Do you want to play the game with colors? \nn counts as a no, any other key pressed would count as a Yes. " << endl;

			char temp = _getch();

			if (tolower(temp) != 'n')
				withColor = true;
			else
				withColor = false;
		}
		else if (choice == '4') {

			levelNames.clear();
			getLevels();
			system("cls");
			cout << banner;

			cout << "Select a level you wish to play by entering it's index (1,2...)\n";
			for (size_t i = 0; i < levelNames.size(); i++)
			{

				std::size_t slash = levelNames[i].find_last_of("\\"); // find last slash in file path
				std::size_t dot = levelNames[i].find_last_of(".screen"); // find where ending .screen

				int a = levelNames[i].substr(slash + 1).length() - 7; // get substring len - ".screen"
				cout << i +1  << ". " << levelNames[i].substr(slash + 1, a) << endl; // file name
			}
			
			string userInput;
			
			std::getline(cin, userInput);

			if (!checkIfInt(userInput))
			{
				cout << "There is no such level\n";
				cout << "Press any key to return to main menu\n";
				_getch();
				continue;
			}
			int selectedLevel = std::stoi(userInput);

			if (selectedLevel >= 1 && selectedLevel <= levelNames.size())
			{
				selectedLevel--;
			}
			else {
				cout << "There is no such level\n";
				cout << "Press any key to return to main menu\n";
				_getch();
				continue;
			}

			string selectedLevelPath = levelNames[selectedLevel];
			levelNames.clear();
			levelNames.push_back(selectedLevelPath);
			singleLevelChosen = true;
		}
		else if (choice == '8') {

			instructions();
		}
		else if (choice == '9') {
			return;
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* pacman_*.screen
* lexicografical order
*/
void Game::getLevels() {

	std::string path = fs::current_path().string();
	for (const auto& entry : fs::directory_iterator(path)) {

		if (std::filesystem::path(entry).extension() == ".screen") {

			levelNames.push_back(entry.path().string());
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Prints the Starting Menu of the game
*  Will print until the user chooses valid input
*/
void Game::printMenu(char& choice) {

	bool check = false;

	system("cls");
	setTextColor(Color::LIGHTGREY);

	cout << banner;
	cout << "Welcome to pacman game :)" << endl;
	cout << "Please select an Option from the screen:" << endl;
	cout << "1. Start Game" << endl;
	cout << "2. Select Game Difficulty" << endl;
	cout << "3. Select Color Mode" << endl;
	cout << "4. Select a Specific level" << endl;
	cout << "8. Present instructions and keys" << endl;
	cout << "9. Exit" << endl;
	
	choice = _getch();

	if (choice >= '1' && choice <= '9')  check = true;

	while (!check) {

		system("cls");

		cout << banner;
		cout << "Welcome to pacman game :)" << endl;
		cout << "Please select an Option from the screen:" << endl;
		cout << "1. Start Game" << endl;
		cout << "2. Select Game Difficulty" << endl;
		cout << "3. Select Color Mode" << endl;
		cout << "4. Select a Specific level" << endl;
		cout << "8. Present instructions and keys" << endl;
		cout << "9. Exit" << endl;
		
		choice = _getch();

		if (choice >= '1' && choice <= '9')

			check = true;
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Prints the instructions of the game
*/
void Game::instructions() {

	system("cls");
	setTextColor(Color::LIGHTGREY);

	cout << banner;
	cout << "PACMAN GAME\n"
		"            \n"
		" Move left:    " << "a" << "\n"
		" Move right:   " << "d" << "\n"
		" Move up:      " << "w" << "\n"
		" Move down:    " << "x" << "\n"
		" Stop move:    " << "s" << "\n"
		"\n"
		" You are PACMAN.       You  look like: " << '@' << "\n"
		" Collect all the dots. They look like: " << FOOD << "\n"
		" Avoid the ghosts.     They look like: " << "&" << "\n"
		"\n"
		" Good luck!\n\n"
		" Press any key to return to Main Menu... \n"
		"\n\n\n";

	_getch();
}

/*----------------------------------------------------------------------------------------------*/
/* Function that runs the actual game loop/logic of the game
*/
bool Game::startGame(Player& player) {

	long int gameLoops = 1;
	
	system("cls");

	printBoard2();

	bool continueGame = false;
	bool MoveGhost = false;
	int MoveFruit = 0;

	int FruitSpawn = rand() % Fruit_Spawn_Rate;

	bool lostGame = false;
	bool wonLevel = false;

	vector <Ghost*> ghosts;

	if (difficultyLevel == BEST) {

		for (int i = 0; i < board2->getGhostNum(); i++) {

			ghosts.push_back(new Ghost_Expert(board2->getGhostsStartPos()[i]));
		}
	}
	else if (difficultyLevel == GOOD) {

		for (int i = 0; i < board2->getGhostNum(); i++) {

			ghosts.push_back(new Ghost_Intermediate(board2->getGhostsStartPos()[i]));
		}
	}
	else {  //difficultyLevel == NOVICE

		for (int i = 0; i < board2->getGhostNum(); i++) {

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

	do {

		printStats(player.getLives(), player.getPoints(), player.getFood());
		hideCursor();
		if (_kbhit()) {

			ch = _getch();
		}

		if (ch == 27) {
			
			system("cls");

			bool esc = printMessage(PAUSE);
			ch = tolower(temp);
			if (esc) {

				return false;
			}

			printBoard2();
		}

		moveFruit(fruit, MoveFruit);
		//write fruit move


		movePlayer(player, ch, temp);
		//write player move to file

		Sleep(SPEED);

		if (_kbhit()) {

			ch = _getch();
		}

		hideCursor();

		if(withColor)
			setTextColor(Color::YELLOW);

		player.draw();

		moveGhosts(ghosts, MoveGhost, player.getPosition());
		//write ghost moves to file

		if (!fruit.getAlive()) {

			fruit.Delete(board);
			FruitSpawn = rand() % Fruit_Spawn_Rate;

			if (FruitSpawn == 0) {
			
				fruit.setAlive(ALIVE,board);
				
				findFruitSpawnPoint(fruit, player, ghosts);

				if (saveMode)
					steps << "Fruit new Position: X: " << fruit.getPosition().getX() << ",Y: " << fruit.getPosition().getY();
			}
		}

		if (checkCollision(player, ghosts))
		{
			if (saveMode)
				result << "Pacman died: " << gameLoops << endl;

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

			if(saveMode)
				result << "Pacman Finished the Screen: " << gameLoops << endl;
		}

		steps << endl;

		gameLoops++;
		
	} while (!lostGame && !wonLevel);

	// free ghost memory:

	for (int i = 0; i < ghosts.size(); i++) {

		delete ghosts[i];
	}

	if (lostGame) {

		return false;
	}

	return true;
	// go to next screen.......................
}

/*----------------------------------------------------------------------------------------------*/
/* Prints in the side of the screen the Player's lives and points
* 
* the LEGENDDD
* 3 rows X 20 cols
*/
void Game::printStats(int lives = 3, int points = 0, int food = 0) {

	board2->getLegendPos();

	setTextColor(Color::LIGHTGREY);

	gotoxy(board2->getLegendPos().getX(), board2->getLegendPos().getY());

	cout << "Lives: " << lives;

	gotoxy(board2->getLegendPos().getX(), board2->getLegendPos().getY() + 1);

	cout << "Points: " << points;
	gotoxy(board2->getLegendPos().getX(), board2->getLegendPos().getY() + 2);

	cout << "Food: " << food;
}

/*----------------------------------------------------------------------------------------------*/
/* Moves the Pacman
*/
void Game:: movePlayer(Player& player, char ch, char& temp) {

	ch = tolower(ch);

	if (ch == UP || ch == DOWN || ch == RIGHT || ch == LEFT)
	{
		temp = ch;
		player.move(ch, board, withColor,board2->getSecretPathWays());
	}
	else if (ch == STAY) {

		temp = ch;
	}
	else {
		player.move(tolower(temp), board, withColor, board2->getSecretPathWays());
	}

	if (saveMode)
		steps << "Pacman: " << temp << " ";
}

/*----------------------------------------------------------------------------------------------*/
/* Prints the board
*/
void Game::printBoard2() {

	for (int row = 0; row < board2->getBoardRows(); row++) {

		for (int col = 0; col < board2->getBoardCols(); col++) {

			if (withColor) {

				if (board[row][col] == FOOD)
					setTextColor(Color::LIGHTGREY);

				else
					setTextColor(Color::BLUE);
			}

			cout << board[row][col];
		}

		cout << endl;
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Moves the ghosts
*/
void Game::moveGhosts(vector<Ghost*>& ghosts, bool& moveTurn, GameObject pacmanPos) {

	// Movement of the Ghosts is half of the movement of Pacman
	moveTurn = !moveTurn;

	if (moveTurn) {

		for (int i = 0; i < ghosts.size(); i++) {

			ghosts[i]->move(board, pacmanPos,ghosts);

			if (saveMode)
				steps << "Ghost" << i << ": " << ghosts[i]->getDirection() << " ";
		}
	}

	Color arr[4] = { Color::RED , Color::MAGENTA, Color::CYAN, Color::BROWN };

	for (int i = 0; i < ghosts.size(); i++) {

		if (withColor)
			setTextColor(arr[i]);
		ghosts[i]->draw();
	}
}

/*----------------------------------------------------------------------------------------------*/
/* moveFruit moves the fruit on the board if it is time for him to move
*/
void Game:: moveFruit(Fruit& fruit, int& moveTurn) {

	fruit.Delete(board);
	if (fruit.getAlive()) {

		// Movement of the Fruit is half of the movement of Ghost
		moveTurn = (moveTurn + 1) % 4;

		if (moveTurn == 1) {

			fruit.move(board);

			if (saveMode)
				steps << "Fruit: " << fruit.getDirection() << " ";
		}

		if (withColor)
			setTextColor(Color::GREEN);
		fruit.draw();
	}
	else  // fruit is DEAD
		fruit.Delete(board);
}

/*----------------------------------------------------------------------------------------------*/
/* Checks if player and ghosts have the same x,y position (if collision)
*/
bool Game::checkCollision(Player player, vector<Ghost*> ghosts) {

	for (int i = 0; i < ghosts.size(); i++) {

		if (player.getX() == ghosts[i]->getX() && player.getY() == ghosts[i]->getY())
		{
			return true;
		}
	}

	return false;
}

/*----------------------------------------------------------------------------------------------*/
/* Returns player and ghosts to their original positions, and substracts 1 point from player's lives \
*/
void Game::respawn(Player& player, vector<Ghost*>& ghosts) {

	player.setLives(player.getLives() - 1); //minus one life

	player.Delete();

	for (int i = 0; i < ghosts.size(); i++) {

		ghosts[i]->Delete(board);
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
/* findFruitSpawnPoint finds a position on the board where the fruit can "safley" spawn.
*/
void Game:: findFruitSpawnPoint(Fruit& fruit, Player player, vector<Ghost*> ghosts) {

	int newX;
	int newY;
	bool OK = false;

	do {
		newX = rand() % board2->getBoardCols();
		newY = rand() % board2->getBoardRows();

		//if (board[newY][newX] == ' ' || board[newY][newX] == FOOD)
		if(board2->getChar(newY,newX) == FOOD)
			OK = true;
		else 
			OK = false;

		if (newX == player.getX() && newY == player.getY())

			OK = false;

		for (int i = 0; i < ghosts.size(); i++) {

			if (newX == ghosts[i]->getX() && newY == ghosts[i]->getY())

				OK = false;
		}

	} while (!OK);

	fruit.setX(newX);
	fruit.setY(newY);
}

/*----------------------------------------------------------------------------------------------*/
/* Checks if player and ghosts have the same x,y position (if collision)
*/
void Game:: checkFruitCollision(Player& player, vector<Ghost*> ghosts, Fruit& fruit) {

	if (fruit.getAlive() && player.getX() == fruit.getX() && player.getY() == fruit.getY())
	{
		for (int i = 0; i < fruit.getValue(); i++) {

			player.addAPoint();
		}

		fruit.setAlive(DEAD,board);
	}

	for (int i = 0; i < ghosts.size(); i++) {

		if (fruit.getAlive() && fruit.getX() == ghosts[i]->getX() && fruit.getY() == ghosts[i]->getY())
		{
			fruit.setAlive(DEAD,board);
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Prints a message if the user WON/LOST/PAUSED the game
*/
bool Game::printMessage(State state) {

	if (withColor)

		setTextColor(Color::YELLOW);

	else
		setTextColor(Color::LIGHTGREY);

	system("cls");

	if (state == WON) {

		cout << congrats;
	}
	else if (state == LOST) {

		cout << youLost;
	}
	else { // state == PAUSE

		cout << paused;
		cout << "TO END GAME PRESS E\n";

		char ch = ' ';

		do {

			if (_kbhit()) {

				ch = _getch();
			}

		} while (ch != 27 && tolower(ch) != 'e');

		system("cls");

		if (tolower(ch) == 'e')
			return true;
		else {
			return false;  // Unpause Game
		}
	}

	cout << "Press any key to go back to the Main Menu... " << endl;

	_getch();  // Waits until the User presses the keyboard

	system("cls");
	return false;
}

/*----------------------------------------------------------------------------------------------*/
/* char Difficulty GETTER
*/
char Game::getDifficulty() const {

	return this->difficultyLevel;
}

/*----------------------------------------------------------------------------------------------*/
/* Difficulty SETTER
*/
void Game::setDifficulty(char diff) {

	this->difficultyLevel = diff;
}

/*----------------------------------------------------------------------------------------------*/
// Save
/*----------------------------------------------------------------------------------------------*/
string Game::fileNameSteps(string fileName) {

	std::size_t slash = fileName.find_last_of("\\"); // find last slash in file path
	std::size_t dot = fileName.find_last_of(".screen"); // find where ending .screen

	int a = fileName.substr(slash + 1).length() - 7; // get substring len - ".screen"
	return fileName.substr(slash + 1, a) + ".steps"; // file name
}

/*----------------------------------------------------------------------------------------------*/

string Game::fileNameResult(string fileName) {

	std::size_t slash = fileName.find_last_of("\\"); // find last slash in file path
	std::size_t dot = fileName.find_last_of(".screen"); // find where ending .screen

	int a = fileName.substr(slash + 1).length() - 7; // get substring len - ".screen"
	return fileName.substr(slash + 1, a) + ".result"; // file name
}

/*----------------------------------------------------------------------------------------------*/

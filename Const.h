/*----------------------------------------------------------------------------------------------*/
/* Utility file that hold the const values of the game
*/
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int terminal_Size_X = 100;
const int terminal_Size_Y = 100;

const int BoardXSize = 54;
const int BoardYSize = 22;

const char FOOD = '°';  
const int SPEED = 120; //120

const int Player1_Starting_Postition_X = 8;
const int Player1_Starting_Postition_Y = 25;

const int Ghost1_Starting_Postition_X = 10;
const int Ghost1_Starting_Postition_Y = 25;

const int Ghost2_Starting_Postition_X = 10; 
const int Ghost2_Starting_Postition_Y = 28;

const int Medium_Dumb_Ghost_Rate = 15;

const int Fruit_Starting_Position_X = 1;
const int Fruit_Starting_Position_Y = 1;
const int Max_Fruit_Steps = 20;   // the maximum number of steps that the fruit will make until it desapears.
const int Fruit_Spawn_Rate = 40;  // the lower the number the higher the probability to spawn a new Fruit.

const int Starting_Lives = 3;

const bool DEAD = 0;
const bool ALIVE = 1;

const char RIGHT = 'd';
const char LEFT = 'a';
const char UP = 'w';
const char DOWN = 'x';
const char STAY = 's';


const char BEST = 'a';
const char GOOD = 'b';
const char NOVICE = 'c';

/*
const char NORMAL = 'n';
const char SAVE = 's';
const char LOAD = 'l';
const char LOADSILENT = 'd';
*/

// Save Mode:

const bool SAVE = true;
const bool LOAD = true;
const bool NORMAL = false;
const bool SILENT = true;

const string banner =
"########################################\n"
"# ____  ____  ____  _      ____  _     #\n"
"#/  __\\/  _ \\/   _\\/ \\__/|/  _ \\/ \\  /|#\n"
"#|  \\/|| / \\||  /  | |\\/||| / \\|| |\\ ||#\n"
"#|  __/| |-|||  \\__| |  ||| |-||| | \\||#\n"
"#\\_/   \\_/ \\|\\____/\\_/  \\|\\_/ \\|\\_/  \\|#\n"
"########################################\n\n";
                                      
const string congrats =
"   _____                            _       _ \n"
"  / ____|                          | |     | |\n"
" | |     ___  _ __   __ _ _ __ __ _| |_ ___| |\n"
" | |    / _ \\| '_ \\ / _` | '__/ _` | __/ __| |\n"
" | |___| (_) | | | | (_| | | | (_| | |_\\__ \\_|\n"
"  \\_____\\___/|_| |_|\\__, |_|  \\__,_|\\__|___(_)\n"
"                     __/ |                    \n"
" __     __          |___/       ___       _   \n"
" \\ \\   / /          \\ \\        / (_)     | | \n"
"  \\ \\_/ /__  _   _   \\ \\  /\\  / / _ _ __ | |  \n"
"   \\   / _ \\| | | |   \\ \\/  \\/ / | | '_ \\| |  \n"
"    | | (_) | |_| |    \\  /\\  /  | | | | |_|  \n"
"    |_|\\___/ \\__,_|     \\/  \\/   |_|_| |_(_)  \n\n\n";
                                              
const string youLost =
"   _____          __  __ ______    ______      ________ _____  \n"
"  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n"
" | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n"
" | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / \n"
" | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n"
"  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\\n\n";

const string paused =

"  ________    _____      _____  ___________   __________  _____   ____ ___  ____________________________   \n"
" /  _____/   /  _  \\    /     \\ \\_   _____/   \\______   \\/  _  \\ |    |   \\/   _____/\\_   _____/\\______ \\  \n"
"/   \\  ___  /  /_\\  \\  /  \\ /  \\ |    __)_     |     ___/  /_\\  \\|    |   /\\_____  \\  |    __)_  |    |  \\ \n"
"\\    \\_\\  \\/    |    \\/    Y    \\|        \\    |    |  /    |    \\    |  / /        \\ |        \\ |    `   \\\n"
" \\______  /\\____|__  /\\____|__  /_______  /    |____|  \\____|__  /______/ /_______  //_______  //_______  /\n"
"        \\/         \\/         \\/        \\/                     \\/                 \\/         \\/         \\/ \n\n"
"Press ESC to continue... \n";

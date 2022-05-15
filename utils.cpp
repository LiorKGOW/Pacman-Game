#include "utils.h"
#include <string>

/*----------------------------------------------------------------------------------------------*/

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

/*----------------------------------------------------------------------------------------------*/

void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

/*----------------------------------------------------------------------------------------------*/

void setTextColor(Color colorToSet) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

/*----------------------------------------------------------------------------------------------*/

bool checkIfInt(std::string s) {

	int i = 0;
	if (s.length() == 0)
	{
		return false;
	}
	for (i; i < s.length(); i++) {

		if (s[i] >= '0' && s[i] <= '9')
		{
			//noting
		}
		else {
			return false;
		}
	}

	return true;
}
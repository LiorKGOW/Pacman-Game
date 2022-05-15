#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "colors.h"
using std::cout;

void gotoxy(int x, int y);
void hideCursor();
void setTextColor(Color color);
bool checkIfInt(std::string s);

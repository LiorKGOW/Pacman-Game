/*----------------------------------------------------------------------------------------------*/
/* Basic Object that holds the (X,Y) position. 
*/
#pragma once
#include <iostream>
#include "Const.h"

class GameObject {

protected:
	int xPos;
	int yPos;

public:
	GameObject(int x = 0, int y = 0) {
		this->xPos = x;
		this->yPos = y;
	};
	void printPos() const;

	bool operator==(const GameObject& other) const {

		return (this->xPos == other.xPos) && (this->yPos == other.yPos);
	}
	GameObject operator+(const GameObject& other) const {

		return GameObject(this->xPos + other.xPos, this->yPos + other.yPos);
	}

	// GETTERS:
	GameObject getPosition() const;
	int getX() const;
	int getY() const;

	// SETTERS:
	void setPosition(GameObject newPos);
	void setX(int newX);
	void setY(int newY);
};
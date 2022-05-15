#pragma once
#include "GameObject.h"
class PathNode
{
private:
	PathNode* parent;
	GameObject position;

	int g;
	int h;
	int f;

public:
	PathNode(GameObject _position, int _g, int _h, PathNode* _parent = nullptr) {

		parent = _parent;
		position = _position;

		g = _g;  // distance between the start node and the current node
		h = _h;  // distance between the current node and the end node
		f = g + h;  // Total cost of the node (g + h)
	}


	bool operator==(PathNode& other) const {

		return (this->position == other.position);
	}

	bool operator!=(PathNode& other) const {

		return !operator==(other);
	}

// GETTERS:
	int getg() const;
	int geth() const;
	int getf() const;
	PathNode* getParent() const;
	const GameObject getPosition() const;

// SETTERS:
	void setg(int newG);
	void seth(int newH);
	void setf(int newF);
	void setParent(PathNode* newParent);
	void setPosition(GameObject newPos);
};


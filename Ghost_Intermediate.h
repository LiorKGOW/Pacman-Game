#pragma once
#include "Ghost.h"

class Ghost_Intermediate : public Ghost
{
public:

    Ghost_Intermediate(int x, int y, bool alive = true, char dir = STAY) : Ghost(x, y, alive, dir) {}
    Ghost_Intermediate(GameObject object, bool alive = true, char dir = STAY) : Ghost(object.getX(), object.getY(), alive, dir) {}

    void move(char board[][terminal_Size_X], GameObject pacmanPos, vector<Ghost*> ghosts) override;  // TODO: Finish setting things up!! this is because we want it to become a pure virtual function!!
};

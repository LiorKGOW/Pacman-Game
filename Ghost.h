/*----------------------------------------------------------------------------------------------*/
/* Represents a Ghost in the game
*  Inherits from gameObject
*/
#pragma once
#include "GameObject.h"
#include "Const.h"
#include "utils.h"
#include "PathNode.h"
#include <vector>
#include <math.h>

/* TODO: add polymorphism:
* TODO: we have 4 classes: Base_Ghost, Novice_Gohst, Intermidiate_Gohst, Expert_Ghost
* Base_Ghost: every function except of move. move => make it a pure virtual function that every Advanced ghost should have.
* Novice: random move
* Intermidiate: move approach?
* Expert: A Star & move approach
* TODO: add A star as an outside function? In Base Ghost?
* TODO: Substract: difficulty.
* TODO: When creating the Ghosts, change the call to the constructor.
* TODO: take off difficulty
* TODO: take off uneccesary comments
*/

class Ghost : public GameObject {

protected:
    char dir;
    bool alive = true;
    // char difficulty;
    int moveCount = 20;

public:
    Ghost(int x, int y,/*char difficulty = BEST,*/ bool alive = true, char dir = STAY) : GameObject(x, y) {
        //this->difficulty = difficulty;
        this->dir = dir;
        this->alive = true;
    };
    Ghost(GameObject go, /*char difficulty = BEST,*/ bool alive = true, char dir = STAY) : GameObject(go.getX(), go.getY()) {
        // this->difficulty = difficulty;
        this->dir = dir;
        this->alive = true;
    };

    virtual void move(char board[][terminal_Size_X], GameObject pacmanPos, vector<Ghost*> ghosts) = 0;  // TODO: Finish setting things up!! this is because we want it to become a pure virtual function!!
    void move(char board[][terminal_Size_X], char direction, vector<Ghost*> ghosts);
    char aStar(char board[][terminal_Size_X], GameObject end, vector<Ghost*> ghosts) ;
    void draw();
    void Delete(char board[][terminal_Size_X]);
    char moveApproc(GameObject end, char board[][terminal_Size_X], vector<Ghost*> ghosts);
    bool checkLegalMove(char direction, char board[][terminal_Size_X], vector<Ghost*> ghosts);
    bool checkLegalMove(GameObject pos, char board[][terminal_Size_X], vector<Ghost*> ghosts);

    // Getters:

    char getDirection() const;
};

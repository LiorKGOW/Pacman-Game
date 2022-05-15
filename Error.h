#pragma once
#include <string>
using std::string;

/*----------------------------------------------------------------------------------------------*/

class Error {

protected:

	string msg;

public:

	Error(const string& s) : msg(s) {}

	string getMsg() { return msg; }
};

/*----------------------------------------------------------------------------------------------*/

class Pacman0Error : public Error {

public:

	Pacman0Error() : Error("Error! \n\nThe Screen didn't have a Pacman, cannot play current Screen \ncontinuing to next Screen... \n") {}
};

/*----------------------------------------------------------------------------------------------*/

class PacmanError : public Error {

public:
	
	PacmanError() : Error("Error! \n\nThe Screen had more then 1 Pacman, cannot play current Screen \ncontinuing to next Screen... \n") {}
};

/*----------------------------------------------------------------------------------------------*/

class Legend0Error : public Error {

public:

	Legend0Error() : Error("Error! \n\nThe Screen didn't have a Legend, cannot play current Screen \ncontinuing to next Screen... \n") {}
};

/*----------------------------------------------------------------------------------------------*/

class LegendError : public Error {

public:

	LegendError() : Error("Error! \n\nThe Screen had more then 1 Legend, cannot play current Screen \ncontinuing to next Screen... \n") {}
};

/*----------------------------------------------------------------------------------------------*/

class GhostError : public Error {

public:

	GhostError() : Error("Error! \n\nThe Screen had more then 4 Ghosts, cannot play current Screen \ncontinuing to next Screen... \n") {}
};

/*----------------------------------------------------------------------------------------------*/

class TunnelError : public Error {

public:

	TunnelError() : Error("Error! \n\nThe Screen had an ilegal Tunnel, cannot play current Screen \ncontinuing to next Screen... \n") {}
};

/*----------------------------------------------------------------------------------------------*/

class GeneralBoardError : public Error {

public:

	GeneralBoardError() : Error("Error! \n\nThis Screen was not legal, cannot play current Screen \ncontinuing to next Screen... \n") {}
};

/*----------------------------------------------------------------------------------------------*/
# Pacman-Game

 ____  ____  ____  _      ____  _     
/  __\/  _ \/   _\/ \__/|/  _ \/ \  /|
|  \/|| / \||  /  | |\/||| / \|| |\ ||
|  __/| |-|||  \__| |  ||| |-||| | \||
\_/   \_/ \|\____/\_/  \|\_/ \|\_/  \|

_Welcome to Pacman !!_

In this game you are Pacman. Your goal is to eat all of the food presented on the screen. When you finish eating all of the food on the screen in all of the levels, you will win.
Beware of the ghosts, they will try to eat you causing you to lose a life (you have 3 lives)

The difficulty of the ghosts is determined by the provided difficulty :
(a) BEST - Ghost try to chase the pacman. the ghost will find a path to the pacman using the A Star pathfinding algorithm.
(b) GOOD - Ghost try to chase the pacman, but occasionally (randomly, once in ~20 moves) they just change to a random direction and stay with it for 5 moves before being smart again
(c) NOVICE - Ghost just move on screen with a direction selected randomly every 20 moves
_Notice: _ You need to choose your difficulty in the menu, the game's default difficulty is BEST.

_Controls:_

w - Up
x - Down
a - Left
d - Right
s - Stay
Esc - Pause

_This program can run in several options:_

1. Normal Mode : with no given arguments.
   In this mode, you can play the regular Pacman game. The levels are played by the files provided In the game current directory with a matching starting name of "pacman\_" and a file extension of ".screen", in lexicographical order.

- _Notice_ An explanation about the format can be found in the file: "file_format"

2. Save Mode : with --save as an argument.
   In this mode, the game runs normally from the player's point of view, but saves only the latest game played in files in the format corresponding the screen name but with a file extension of ".steps" & ".result", which describe the game played by the user.

3. Load Mode : with --load as an argument.
   In this mode, there is no displayed menu. The program just displays the game discribed in the ".Steps" files in lexicographical order, and finishes. This mode ignores all user input.

- _Notice_ If there are no files, a proper message would be presented on the screen when trying to start a new game.

4. Load Silent Mode : with -load -silent as arguments.
   In this mode, the game runs the files provided in the local directory staring with "pacman\_", and a file extension of ".steps" , in lexicographical order, and compares the result of its described game with a matching name and a file extension of ".result" consisting an expected result.
   Whether the result is the same or not , an appropriate message would be displayed on the screen (test passed / failed).

- _Notice_ it is the responsibility of the screen designer to make sure that the & is placed in a position not accessible by the creatures !
  Be sure to read the file_format file carefully to prevent any bugs.

  _If you encounter any bugs, please report them to me GLHF :)_

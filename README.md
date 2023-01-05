# 8-Tile-Puzzle

This is a C++ program that solves 8-tile puzzles inputted as command line arguments.  8-tile puzzles are games that involve a 9x9 grid of a picture (in this case each
space is a number 0-9) with exactly one empty space allowing for one tile at a time to move a space over.  Using a breadth first search approach, the program will 
check if a board is solvableand then print out the moves used to reach the goal board.  In this implementation, the goal board is '123456780' where '0' is the empty 
space.

## How to Use

When running the code via terminal, you may input as many command line arguments as you like, and the code will check if the given boards are valid.  One example of
a valid board argument is '341270586'.

// COCS 2436 Final Project Spikes A-G
// Team 2 ( Etheridge Mixon, Eduardo Palacios & Kai Aweau)
// *****
// This is a program that takes in an arbitrary number of starting 8 puzzle game boards as command line arguments 
// and finds the fastest path to a solution.  The program will print how many moves were considered for each
// board and list the moves used to reach a solution.
// *****
//  Test executions
//  SolvePuzzles: 812043765 182043765 345712860 123456780 812043765 234135679 987654321

#include <iostream>
#include "board.h"
#include "move.h"
#include <map>
#include <queue>

using namespace std;

int main(int argc, char *argv[]){
    if (argc < 2){  // If no boards given
        std::cout << "Usage: solvePuzzle initalBoard " << std::endl;
        return -1;
    }

    std::queue<boardType> gamesQueue; 
        // Create a queue in the instance that multiple boards are inputted -- SPIKE D
    vector<pair<boardType, int> > solutions;     // SPIKE F

    for (int i = 1; i < argc; i++){ 
        boardType inBoard(argv[i]);
            // each argument is made into a boardType
        gamesQueue.push(inBoard);
            // add into queue
    }

    while (!gamesQueue.empty()){
        boardType &board = gamesQueue.front();  // First board in
        gamesQueue.pop();                       // First board out
        std::cout << "------------------------------------" << std::endl;  //seperate games for visibility
        std::cout << "Game Board Puzzle :\n"
                  << board;                     // print out initial board
        if (!board.isSolvable()){               // Check solvability, if not solvable, go into next board -- SPIKE B
            std::cout << "\nGame Board is not solvable " << std::endl
                      << std::endl;
            continue;
        }
        std::cout << std::endl << std::endl;

        map<int, boardType> visited_boards;     // SPIKE E
        queue<boardType> to_consider_boards;    // a queue for next possible boards

        to_consider_boards.push(board);         // start with original board

        boardType goalBoard("123456780");       // SPIKE A

        int moves_considered = 0;

        while (!to_consider_boards.empty()){                    // go through possible boards 
            boardType cur_board = to_consider_boards.front();   // take first out of the queue
            to_consider_boards.pop();
            
            if (cur_board.convert_matrix_to_string() ==
                goalBoard.convert_matrix_to_string()){          // if we are already at the goal, stop looking
                solutions.push_back(make_pair(cur_board, moves_considered));    // know where to start making the path
                break;
            }
            moves_considered++;                                 // if we aren't at the goal, start looking at options

            visited_boards.insert(make_pair(cur_board.calculateHashKey(), cur_board));    //add onto visited_boards

            vector<MoveType> next_moves = cur_board.generate_next_states();     // vector of all possible next moves

            for (auto m : next_moves){                          // for each possible move, make the move and check
                boardType next_board = cur_board;               //  if the resulting board has been visited
                next_board.make_move(m);                 

                if (visited_boards.count(next_board.calculateHashKey()) == 0) {     // if board has not been visited,
                    to_consider_boards.push(next_board);                            //  push board to queue of boards
                }                                                                   //  to consider next
            }
        }

        for (auto sol : solutions){         // Output moves considered, and path for puzzle -- SPIKE G
            cout << "******Game Board Goal Reached*******" << endl
                 << endl;
            cout << "Moves that were considered: " << sol.second << endl
                 << endl;
            cout << "Solutions generated to solve Game Board Puzzle:  " << endl;
            for (auto m_i = sol.first.begin(); m_i != sol.first.end(); m_i++){
                cout << *m_i << endl;
            }
            solutions.resize(0);
        }
    }
    return 0;
}
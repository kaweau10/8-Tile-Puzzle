// COCS 2436 Final Project Spikes A-G
// Team 2 - (Etheirdge Mixon, Eduardo Palacios & Kai Aweau)

#ifndef BOARD_TYPE_H
#define BOARD_TYPE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include "move.h"

using namespace std;

class boardType {
    public:
        boardType(std::string init = "123456780");
            // constructor
        
        bool isSolvable();
            // SPIKE B
            // Before calculating inversions, will test conditions for board to see
            //      if board is a proper board.
            // Check inversions for the board; returns(inversions %2 == 0)
        
        vector<char> convert_matrix_to_string();
            // convert state to string by returning a vector of characters
        
        vector<MoveType>  generate_next_states();
            // add possible states from current state -- SPIKE C

        void make_move(MoveType move);  
            // make a move by altering the board based on the given MoveType 
        
        int calculateHashKey();
            // calculate and returns hash function of map layout

        vector<MoveType>::const_iterator begin() const;
        vector<MoveType>::const_iterator end() const;
            // Iterator functions to go thru moves
        
        friend std::ostream& operator<<(std::ostream& os, const boardType& dt);
            // overload the stream insertion operator for output capabilities
    private:
        int board[3][3];
        vector<MoveType> moves;     // SPIKE F & G
};

boardType::boardType(std::string argv) {
        // fill initial board from argv
        // assumes valid array of integers
    int iPos = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            board[row][col] = argv[iPos++] - '0' ;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const boardType& thisBoard) { //override to print out 
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            os << thisBoard.board[r][c] << ' ';
        }
        std::cout << std::endl;
    }
    return os;
}

vector<char> boardType::convert_matrix_to_string(){
    vector<char> linear;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            linear.push_back(board[i][j]);
        }
    }
    return linear;
}

bool boardType::isSolvable(){
    std::vector<int> location;  //will convert array onto a vector
    int inversions = 0;
    for (int row = 0; row < 3; row++){  //put each element of the board into vector using push_back
        for (int col = 0; col < 3; col++){
            location.push_back(board[row][col]);
        }
    }

    set<int> vals;
    for (auto ch : location){   //insert the locations of the numbers into a set of values for comparison
        vals.insert(ch);
    }
    if (vals.size() != 9){  //if the board does not have 9 elements
        return false;
    }
    if (!((*(vals.begin()) == 0) && (*(vals.rbegin()) == 8))){ //checks for proper values in board exist
        return false;
    }
    //check if current element is more than the next to increase inversion
    for (unsigned long currentLoc = 0; currentLoc < location.size(); currentLoc++){
        if (location.at(currentLoc) != 0){
            for (unsigned long nextLoc = currentLoc + 1; nextLoc < location.size(); nextLoc++){
                if (location.at(nextLoc)!= 0 && (location.at(currentLoc) > location.at(nextLoc))){
                    inversions++;
                }
            }
        }
    }
    return ((inversions % 2) == 0);
}

void boardType::make_move(MoveType move){   
        // Get move location data by using functions from MoveType
    int temp = board[move.GetFromRow()][move.GetFromCol()];
    board[move.GetFromRow()][move.GetFromCol()] = board[move.GetToRow()][move.GetToCol()];
    board[move.GetToRow()][move.GetToCol()] = temp;
    moves.push_back(move);
}

vector<MoveType> boardType::generate_next_states(){
    vector<MoveType> moves;

    int moving_r = 0; int moving_c = 0;
    int zero_r = 0; int zero_c = 0; 
        // zero_c=column at zero index & zero_r=row at zero index of board.
    for (int i = 0; i < 3; i++){    // checks where "0" is in the board
        for (int j = 0; j < 3; j++){
            if (board[i][j] == 0){ 
                zero_r = i;
                zero_c = j;
            }
        }
    }
    bool u, d, r, l;    // varibales: u=up, d=down, r=right, l=left 2 switch statements intialize variables bool variables indicate 
                        //      possible movements, max is 4 movement when 0 is in middle of board
    moving_r = zero_r;
    moving_c = zero_c;  // varibales to show board tile movements

    switch (zero_c){    // if zero is the tile posistion on one of the edge of board, then its limited to certain
                        // movements.
    case 0:             // when 0(empty space) is at colunm 0 index, cannot move to the right
        r = false;
        l = true;
        break;
    case 1:             // if 0 is at column 1 indext then you can move to right or left
        r = true;
        l = true;
        break;
    case 2:             // when 0 (empty space) it at colunm 2 index, cannot move to the left
        r = true;
        l = false;
        break;
    }
    switch (zero_r){
    case 0:             // if 0 is at row index 0, then movement cannot go down
        d = false;
        u = true;
        break;
    case 1:             // if 0 is at column 1 index, then you can move to up or down
        d = true;
        u = true;
        break;
    case 2:             // if 0 is at row index 2, then movement cannot go up
        d = true;
        u = false;
        break;
    }
        // if statements to perform the actual up,down,right,left movements & "swap" tile with 0 with another tile.
    if (d){             // down move
        moving_r = zero_r - 1;
        moving_c = zero_c;
        moves.push_back(MoveType(moving_r, moving_c, zero_r, zero_c)); // this keeps track of previous movement
    }

    if (u){             // up move
        moving_r = zero_r + 1;
        moving_c = zero_c;
        moves.push_back(MoveType(moving_r, moving_c, zero_r, zero_c));
    }
    if (r){             // right move
    
        moving_r = zero_r;
        moving_c = zero_c - 1;
        moves.push_back(MoveType(moving_r, moving_c, zero_r, zero_c));
    }
    if (l){          // left move
        moving_r = zero_r;
        moving_c = zero_c + 1;
        moves.push_back(MoveType(moving_r, moving_c, zero_r, zero_c));
    }
    return moves;
}

int boardType::calculateHashKey() { 
        //should be the same value for boards that are rotated versions of the board
    int dr; int dc; int d;
    bool rFirst;

    std::hash<std::string> str_hash;

    d = board[0][0];  // assume board[0][0] is lowest digit
    dr = +1;
    dc = +1;
    rFirst = true;

    if (board[0][2] < d) {
        d = board[0][2];
        dr = +1;
        dc = -1;
        rFirst = false;
    }
    if (board[2][2] < d) {
        d = board[2][2];
        dr = -1;
        dc = -1;
        rFirst = true;
    }
    if (board[2][0] < d) {
        d = board[2][0];
        dr = -1;
        dc = +1;
        rFirst = false;
    }

    std::ostringstream s;

    if (rFirst) {
        for (int r = -dr + 1; dr * r <= dr + 1; r += dr) {
            for (int c = -dc + 1; dc * c <= dc + 1; c += dc) {
                s << board[r][c];
            }
        }
    }else {
        for (int c = -dc + 1; dc * c <= dc + 1; c += dc) {
            for (int r = -dr + 1; dr * r <= dr + 1; r += dr) {
                s << board[r][c];
            }
        }
    }
    return (str_hash(s.str()));
}

vector<MoveType>::const_iterator boardType::begin() const{
    return moves.begin();
}

vector<MoveType>::const_iterator boardType::end() const {
    return moves.end();
}

#endif
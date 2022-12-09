// COCS 2436 Final Project Spikes A-G
// Team 2 (Etheirdge Mixon, Eduardo Palacios & Kai Aweau)

#ifndef MOVE_H
#define MOVE_H

#include <iostream>

using namespace std;

class MoveType{     // SPIKE G
    public:
        MoveType(int fromR, int fromC, int toR, int toC){
            fromRow = fromR;
            fromCol = fromC;
            toRow = toR;
            toCol = toC;
        }
        int GetFromRow() { return fromRow; }
        int GetFromCol() { return fromCol; }
        int GetToRow() { return toRow; }
        int GetToCol() { return toCol; }
        friend ostream & operator << (ostream & stream, const MoveType & move);
    private:    
        int fromRow;
        int fromCol;
        int toRow;
        int toCol;    
};

ostream & operator << (ostream & stream, const MoveType & move){ //override for proper print out feature
    stream << "(" << move.fromRow << "," << move.fromCol << ")->(" << move.toRow << "," << move.toCol << ")"; 
    return stream;
}
#endif
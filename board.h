#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <array>

const int BOARD_SIZE =  8;
using ROW = array<Piece*, BOARD_SIZE>;
using BOARD =  array<ROW, BOARD_SIZE>;


enum class SquareState {
    INVALID,
    EMPTY,
    TAKEN_BY_ENEMY,
    TAKEN_BY_FRIENDLY};

class Board
{
    public:
        Board();
        Board(const Board &board);
        ~Board();
        
        void Move(POS start, POS end); //Assuming that the move is valid!!! (checks are made inside game class)
        void PrintBoard() const; //Prints the board in terminal
        SquareState CheckSquare(POS pos, Color color) const; //Checks the state of the square
        Piece* GetPiece(POS pos) const; //Returns the piece pointer at the given position
        bool IsSquareChecked(POS pos, Color color) const; //Checks if the square is under attack by the enemy
        bool IsMoveValid(POS start, POS end, Color color) const; //Checks if the move is valid without actually making the move
        POS GetEnPassant() const; //Returns the en passant square

    private:
        void CreateBoard(); // creates the pieces and places pointers to them on the board
        void UpdateKingPOS(POS end); //Called only after king moves, updates the king's position assuming that the POS end is the king's new position
        void NukeTile(POS pos); //If there is a piece at the given position, delete it and replace with null ptr
        POS GetKingPOS(Color color) const; //Returns the position of the king of the given color
        BOARD board; //2d array of Piece* pointers
        POS whiteKing; //Position of the white king
        POS blackKing; //Position of the black king
        POS enPassant; //Position of the en passant square
};


#endif
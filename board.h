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
        void CreateBoard();
        void PrintBoard();
        void Move(POS start, POS end);
        void NukeTile(POS pos);
        bool IsSquareChecked(POS pos, Color color);
        SquareState CheckSquare(POS pos, Color color);
        Piece* GetPiece(POS pos);

    private:
        BOARD board;
        Piece* whiteKing;
        Piece* blackKing;


};


#endif
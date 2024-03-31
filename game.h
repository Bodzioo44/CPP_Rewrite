#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game
{
    public:
        Game(Color player_color_in);
        void Select(POS pos);
        void ChangeTurn();
        Board& GetBoard();
        MOVES GetHighlightedSquares();
    private:
        Color turn;
        Color player_color;
        //make board public?
        Board board; //so this initializes the board even before the constructor is called.
        Piece* selected;
        MOVES valid_moves;
        MOVES highlighted_squares;
        bool running;
};

#endif
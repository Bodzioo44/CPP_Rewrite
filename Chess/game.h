#ifndef GAME_H
#define GAME_H

#include <algorithm>

#include "Chess/board.h"

class GameWidget;


#include <iostream>
using namespace std;

namespace Chess_2
{
    class Game
    {
        public:
            Game(Color player_color_in, GameWidget* game_widget);
            void Select(POS pos); //Called by the parent widget, when a square is clicked
            void ReceiveUpdate(QJsonObject jsonMessage); //Called by the parent widget whenver a move is received
            Board& GetBoard(); //Called by the parent widget to draw the board
            MOVES GetHighlightedSquares() const; //Called by the parent widget to draw the highlighted squares

        private:
            string CheckForPromotion(); //Called inside Select, checks if PopupBox should be called through parent widget (move actuall check inside board class)
            void ChangeTurn();

            Color turn;
            Color player_color;
            
            Board board; //so this initializes the board even before the constructor is called.
            Piece* selected; //ptr to currently selected piece.

            POS selected_pos; //posision of the selected piece. (since piece doesnt store its location anymore)
            MOVES valid_moves; //valid moves for the selected piece.
            MOVES highlighted_squares; //squares that are highlighted.

            bool running; //state of the game? move inside GameWidget since the loop is there?

            GameWidget* game_widget; //Parent widget
    };
}

#endif
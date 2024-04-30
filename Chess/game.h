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
            void Select(POS pos);
            void ReceiveUpdate(QJsonObject jsonMessage);

            Board& GetBoard(); //change to copy instead of reference?
            MOVES GetHighlightedSquares();

        private:
            string CheckForPromotion();
            void ChangeTurn();

            Color turn;
            Color player_color;
            //make board public?
            Board board; //so this initializes the board even before the constructor is called.
            Piece* selected;
            POS selected_pos;
            MOVES valid_moves;
            MOVES highlighted_squares;
            bool running;

            //needed to somehow communicate with the GUI?
            GameWidget* game_widget;
    };
}

#endif
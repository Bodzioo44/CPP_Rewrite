#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "Chess/game.h"

enum class GameType
{
    CHESS_2,
    CHECKERS_2,
    CHESS_4
};

class GameWidget : public QWidget
{
    
    public:
        GameWidget(GameType game_type, Color player_color);
        //TODO make Draw methods depend on the board, its 8x8 rn.
        void paintEvent(QPaintEvent*);
        void mousePressEvent(QMouseEvent*);
        void resizeEvent(QResizeEvent*);
        void DrawSquares(QPainter &painter);
        void DrawPieces(QPainter &painter);
        void DrawHighlight(QPainter &painter, MOVES squares);
    protected:
        constexpr static float scale = 0.75;
        int square_size;
        Game game; //however this doesnt initialize the game, since the game doesnt have a default constructor.
};


#endif

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QPushButton>

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QImage>

#include <QtCore/QObject>

#include "Chess/game.h"


enum class GameType
{
    CHESS_2,
    CHECKERS_2,
    CHESS_4
};

using namespace Chess_2;

class GameWidget : public QWidget
{
    Q_OBJECT

    public:
        GameWidget();
        ~GameWidget();
        void SetGame(GameType game_type, Color player_color);
        //TODO make Draw methods depend on the board, its 8x8 rn.
        void paintEvent(QPaintEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void resizeEvent(QResizeEvent* event);
        void DrawSquares(QPainter &painter);
        void DrawPieces(QPainter &painter);
        void DrawHighlight(QPainter &painter, MOVES squares);

        //Game-GameWidget communication
        void SendMove(QJsonArray jsonMessage);
        string PopUpPromotionBox();

    private:
        

    signals:
        void MoveMade(QJsonArray jsonMessage);

    protected:
        constexpr static float scale = 0.75;
        int square_size;
        GameType game_type;
        //Add shared class for more games later on?
        Game* game;
};


#endif

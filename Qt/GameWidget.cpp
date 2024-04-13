#include "Qt/GameWidget.h"



//TODO add check if the game exists? bound game exists to the widget? idk
GameWidget::GameWidget() {}
GameWidget::~GameWidget() {delete game;}

void GameWidget::SetGame(GameType game_type_in, Color player_color_in)
{
    game_type = game_type_in;
    game = new Game(player_color_in, this);
}


// void GameWidget::SendMove(POS start, POS end, POS removed)
// {

//     // QJsonArray start_pair {start.first, start.second};
//     // QJsonArray end_pair {end.first, end.second};
//     // QJsonArray removed_pair {removed.first, removed.second};
    
//     // QJsonObject jsonMessage_part {{"START", start_pair}, {"END", end_pair}, {"REMOVED", removed_pair}};
//     // QJsonObject jsonMessage {{GAME_UPDATE, jsonMessage_part}};

//     // parent->SendData(jsonMessage);
// }

//TODO Fix the damn scaling, so it keep ratio, and stays a square!
void GameWidget::resizeEvent(QResizeEvent*)
{
    //QWidget::resizeEvent(event);
    QSize size = this->size();
    int width = size.width();
    int height = size.height();
    square_size = min(width, height) / 8;
    update();
}

void GameWidget::mousePressEvent(QMouseEvent* event)
{
    //QWidget::mousePressEvent(event);
    QPointF pos = event->position();
    int x = pos.x();
    int y = pos.y();
    int row = y / square_size;
    int col = x / square_size;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        //cout << "Clicked on " << row << ", " << col << endl;
        game->Select(make_pair(row, col));
        update();
    }
    else {cout << "Clicked outside the board" << endl;}
}

//Called on each rescale
void GameWidget::paintEvent(QPaintEvent*)
{
    //QWidget::paintEvent(event);
    QPainter painter(this);
    DrawSquares(painter);   
    DrawPieces(painter);
    DrawHighlight(painter, game->GetHighlightedSquares());
}

void GameWidget::DrawHighlight(QPainter &painter, MOVES squares)
{
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);
    for (POS pos : squares)
    {
        painter.drawRect(pos.second * square_size, pos.first * square_size, square_size, square_size);
    }
}

void GameWidget::DrawSquares(QPainter &painter)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                painter.fillRect(j * square_size, i * square_size, square_size, square_size, Qt::white);
            }
            else
            {
                painter.fillRect(j * square_size, i * square_size, square_size, square_size, Qt::gray);
            }
        }
    }
}

//TODO instead of creating a new image each time, create a map of images
//and rescale images inside map on each rescale call
void GameWidget::DrawPieces(QPainter &painter)
{  
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece* p = game->GetBoard().GetPiece(make_pair(i, j));
            if (p != nullptr)
            {   
                QImage image(p->GetPath().c_str());
                //TODO: scale the image properly, its being stretched to square rn. (check the image size (x,y) and draw it accordingly)
                image = image.scaled(square_size * scale, square_size*scale, Qt::IgnoreAspectRatio, Qt::FastTransformation);
                painter.drawImage(j * square_size + (square_size - square_size * scale)/2, i * square_size + (square_size - square_size * scale)/2, image);
            }
        }
    }
}
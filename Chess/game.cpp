
#include "Chess/game.h"
#include "Qt/GameWidget.h"

using namespace Chess_2;

Game::Game(Color player_color_in, GameWidget* game_widget_in)
{
    player_color = player_color_in;
    turn = Color::WHITE;
    highlighted_squares = {};
    running = true;
    selected = nullptr;
    game_widget = game_widget_in;
}

//TODO: Test this
void Game::ReceiveUpdate(QJsonObject jsonMessage)
{
    for (QString key : jsonMessage.keys())
    {
        if (key == "Start")
        {
            QJsonArray move = jsonMessage[key].toArray();
            POS start = POS(move[0].toInt(), move[1].toInt());
            POS end = POS(jsonMessage["End"].toArray()[0].toInt(), jsonMessage["End"].toArray()[1].toInt());
            board.Move(start, end);
            ChangeTurn();
        }
        else if (key == "Promotion")
        {
            QJsonArray promotion = jsonMessage[key].toArray();
            POS pos = POS(promotion[0].toInt(), promotion[1].toInt());
            string piece = promotion[2].toString().toStdString();
            board.Promote(pos, piece);
        }
        else if (key == "Removed")
        {
            QJsonArray removed = jsonMessage[key].toArray();
            POS pos = POS(removed[0].toInt(), removed[1].toInt());
            board.NukeTile(pos);
        }
    }
}


void Game::Select(POS pos)
{
    int row = pos.first;
    int col = pos.second;
    Piece* current_square = board.GetPiece(pos);

    if (selected == nullptr && current_square != nullptr)
    {
        if (current_square->GetColor() != turn)
        {
            cout << "Not your turn!" << endl;
        }
        else
        {
            selected = current_square;
            selected_pos = pos;
            cout << "Selected: " << selected->Info() << endl;
            valid_moves = selected->ValidMoves(board, selected_pos);

            cout << "Valid moves: ";
            for (POS move : valid_moves)
            {
                cout << "(" << move.first << ", " << move.second << ") ";
            }
            cout << endl;

            if (valid_moves.size() != 0)
            {
                highlighted_squares = valid_moves;
            }
            else
            {
                cout << "No valid moves!" << endl;
                selected = nullptr;
            }
        }
    }
    else if (selected != nullptr && selected == current_square)
    {
        cout << "Deselected: " << selected->Info() << endl;
        highlighted_squares.clear();
        selected = nullptr;
    }
    else if (selected != nullptr)
    {
        if (find(valid_moves.begin(), valid_moves.end(), pos) != valid_moves.end())
        {
            cout << "Moving: " << selected->Info() << " to: " << row << ", " << col << endl;
            QJsonArray Moves = board.Move(selected_pos, pos);
            QJsonObject Promotion = CheckForPromotion();
            if (!Promotion.isEmpty())
            {
                Moves.push_back(Promotion);
            }
            
            game_widget->SendMove(Moves);

            highlighted_squares.clear();
            ChangeTurn();
            selected = nullptr;
        }
    }

}


MOVES Game::GetHighlightedSquares()
{
    return highlighted_squares;
}


QJsonObject Game::CheckForPromotion()
{
    QJsonObject Action = {};
    for (int i = 0; i < 8; i++)
    {
        if (board.GetPiece(POS(0, i)) != nullptr && board.GetPiece(POS(0, i))->GetName() == "Pawn")
        {
            string promotion = game_widget->PopUpPromotionBox();
            board.Promote(POS(0, i), promotion);

            Action["Promotion"] = QJsonArray({0,i});
            Action["Removed"] = QJsonArray({0,i});

        }
        else if (board.GetPiece(POS(7, i)) != nullptr && board.GetPiece(POS(7, i))->GetName() == "Pawn")
        {
            string promotion = game_widget->PopUpPromotionBox();
            cout << "We got here" << endl;
            board.Promote(POS(7, i), promotion);
            Action["Promotion"] = QJsonArray({7,i});
            Action["Removed"] = QJsonArray({7,i});
        }
    }
    return Action;
    
}

void Game::ChangeTurn()
{
    if (turn == Color::WHITE)
    {
        turn = Color::BLACK;
    }
    else
    {
        turn = Color::WHITE;
    }
}


Board& Game::GetBoard()
{
    return board;
}
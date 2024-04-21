
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

MOVES Game::GetHighlightedSquares()
{
    return highlighted_squares;
}

void Game::CheckForPromotion()
{
    for (int i = 0; i < 8; i++)
    {
        if (board.GetPiece(POS(0, i)) != nullptr && board.GetPiece(POS(0, i))->GetName() == "Pawn")
        {}
    }
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
            
            game_widget->SendMove(Moves);

            /*
            QJsonDocument doc(Moves);
            cout << doc.toJson().toStdString() << endl;

            for (auto Action : Moves)
            {
                cout << typeid(Action).name() << endl;
                QJsonObject Action_obj = Action.toObject();
                cout << typeid(Action_obj).name() << endl;
                for (auto key : Action_obj.keys())
                {
                    cout << key.toStdString() << endl;
                }
                if (Action_obj.contains("Starting"))
                {
                    cout << "Starting: " << Action_obj["Starting"].toArray()[0].toInt() << ", " << Action_obj["Starting"].toArray()[1].toInt() << endl;
                }
                QJsonArray Starting = Action_obj["Start"].toArray();
                QJsonArray Ending = Action_obj["Ending"].toArray();
                
                for (auto val : Starting)
                {
                    cout << "we are here";
                    cout << typeid(val).name() << endl;
                    cout << val.toInt() << endl;
                }
                for (auto val : Ending)
                {
                    cout << val.toInt() << endl;
                }
                
            }
            
            for (QJsonValue Action: Moves)
            {
                if (Action.isObject())
                {
                    QJsonObject Action_obj = Action.toObject();

                    POS start = make_pair(Action_obj["Starting"].toArray()[0].toInt(), Action_obj["Starting"].toArray()[1].toInt());
                    POS end = make_pair(Action_obj["Ending"].toArray()[0].toInt(), Action_obj["Ending"].toArray()[1].toInt());
                    //POS deleted = make_pair(Action_obj["Deleted"].toArray()[0].toInt(), Action_obj["Deleted"].toArray()[1].toInt());
                    cout << "Starting: " << start.first << ", " << start.second << endl;
                    cout << "Ending: " << end.first << ", " << end.second << endl;
                    //cout << "Deleted: " << deleted.first << ", " << deleted.second << endl;
                }
            }
            */

            highlighted_squares.clear();
            ChangeTurn();
            selected = nullptr;
        }
    }

}


Board& Game::GetBoard()
{
    return board;
}
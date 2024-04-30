
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

//TODO: Fix this
void Game::ReceiveUpdate(QJsonObject jsonMessage)
{

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
            QJsonObject Moves = board.Move(selected_pos, pos);
            string Promotion = CheckForPromotion();
            if (Promotion.size() != 0)
            {
                Moves["type"] = "promotion";
                Moves["additional_data"] = QString::fromStdString(Promotion);
            }
            
            QJsonObject Key_Moves;
            Key_Moves["Game_Update"] = Moves;
            game_widget->SendMove(Key_Moves);

            highlighted_squares.clear();
            ChangeTurn();
            selected = nullptr;
        }
    }

}

string Game::CheckForPromotion()
{
    for (int i = 0; i < 8; i++)
    {
        if (board.GetPiece(POS(0, i)) != nullptr && board.GetPiece(POS(0, i))->GetName() == "Pawn")
        {
            string promotion = game_widget->PopUpPromotionBox();
            board.Promote(POS(0, i), promotion);
            return promotion;

        }
        else if (board.GetPiece(POS(7, i)) != nullptr && board.GetPiece(POS(7, i))->GetName() == "Pawn")
        {
            string promotion = game_widget->PopUpPromotionBox();
            cout << "We got here" << endl;
            board.Promote(POS(7, i), promotion);
            return promotion;
        }
    }
    return "";
    
}


MOVES Game::GetHighlightedSquares()
{
    return highlighted_squares;
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
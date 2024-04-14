
#include "Chess/game.h"
#include "Qt/GameWidget.h"


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
                cout << "(" <<move.first << ", " << move.second << ") ";
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
            board.Move(selected_pos, pos);
            highlighted_squares.clear();
            //call update?
            //promotion check
            ChangeTurn();
            selected = nullptr;
        }
    }

}


Board& Game::GetBoard()
{
    return board;
}
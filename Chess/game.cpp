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

void Game::ReceiveUpdate(QJsonObject Move)
{
    int fromX = Move["fromX"].toInt();
    int fromY = Move["fromY"].toInt();
    int toX = Move["toX"].toInt();
    int toY = Move["toY"].toInt();
    string type = Move["type"].toString().toStdString();
    string additional_data = Move["additional_data"].toString().toStdString();
    //cout << "From: " << fromX << ", " << fromY << " To: " << toX << ", " << toY << " Type: " << type << endl;
    POS start = POS(fromX, fromY);
    POS end = POS(toX, toY);

    if (type == "promotion") //Remove type key? just check if additional_data is empty?
    {
        board.Move(start, end);
        board.Promote(end, additional_data);
    }
    else
    {
        board.Move(start, end);
    }
    ChangeTurn();
}

void Game::Select(POS pos)
{
    int row = pos.first;
    int col = pos.second;
    Piece* current_square = board.GetPiece(pos);

    if (selected == nullptr && current_square != nullptr && turn == player_color)
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
    else if (player_color != turn) {std::cout << "Not your turn" << endl;}
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
            //QJsonObject Key_Moves;
            //Key_Moves["Game_Update"] = Moves;
            game_widget->SendMove(Moves);
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
            board.Promote(POS(7, i), promotion);
            return promotion;
        }
    }
    return "";
    
}


MOVES Game::GetHighlightedSquares() const
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
    cout << "Turn Changed!" << endl;
}


Board& Game::GetBoard()
{
    return board;
}
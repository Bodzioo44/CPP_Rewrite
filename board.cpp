#include <iostream>
#include "board.h"
using namespace std;


Board::Board()
{
    board = {};
    CreateBoard();
    PrintBoard();
}

bool Board::IsSquareChecked(POS pos, Color color)
{
    //Queen and Rook check
    MOVES directions = {POS(1, 0), POS(-1, 0), POS(0, 1), POS(0, -1)};
    for (POS dir : directions)
    {
        POS temp = pos;
        while (true)
        {
            temp.first += dir.first;
            temp.second += dir.second;
            SquareState state = CheckSquare(temp, color);
            if (state == SquareState::INVALID)
            {
                break;
            }
            else if (state == SquareState::EMPTY)
            {
                continue;
            }
            else if (state == SquareState::TAKEN_BY_FRIENDLY)
            {
                break;
            }
            else if (state == SquareState::TAKEN_BY_ENEMY)
            {
                Piece* p = GetPiece(temp);
                if (p->GetName() == "Queen" || p->GetName() == "Rook")
                {
                    return true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    //Queen and Bishop check
    directions = {POS(1, 1), POS(-1, -1), POS(1, -1), POS(-1, 1)};
    for (POS dir : directions)
    {
        POS temp = pos;
        while (true)
        {
            temp.first += dir.first;
            temp.second += dir.second;
            SquareState state = CheckSquare(temp, color);
            if (state == SquareState::INVALID)
            {
                break;
            }
            else if (state == SquareState::EMPTY)
            {
                continue;
            }
            else if (state == SquareState::TAKEN_BY_FRIENDLY)
            {
                break;
            }
            else if (state == SquareState::TAKEN_BY_ENEMY)
            {
                Piece* p = GetPiece(temp);
                if (p->GetName() == "Queen" || p->GetName() == "Bishop")
                {
                    return true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    //Knight check
    directions = {POS(2, 1), POS(2, -1), POS(-2, 1), POS(-2, -1), POS(1, 2), POS(1, -2), POS(-1, 2), POS(-1, -2)};
    for (POS dir : directions)
    {
        SquareState state = CheckSquare(dir, color);
        if (state == SquareState::TAKEN_BY_ENEMY)
        {
            Piece* p = GetPiece(dir);
            if (p->GetName() == "Knight")
            {
                return true;
            }
        }
    }
    //Pawn check
    switch (color)
    {
        case Color::WHITE:
            if (CheckSquare(POS(pos.first + 1, pos.second + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                Piece* p = GetPiece(POS(pos.first + 1, pos.second + 1));
                if (p->GetName() == "Pawn")
                {
                    return true;
                }
            }
            if (CheckSquare(POS(pos.first + 1, pos.second - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                Piece* p = GetPiece(POS(pos.first + 1, pos.second - 1));
                if (p->GetName() == "Pawn")
                {
                    return true;
                }
            }
            break;
        case Color::BLACK:
            if (CheckSquare(POS(pos.first - 1, pos.second + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                Piece* p = GetPiece(POS(pos.first - 1, pos.second + 1));
                if (p->GetName() == "Pawn")
                {
                    return true;
                }
            }
            if (CheckSquare(POS(pos.first - 1, pos.second - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                Piece* p = GetPiece(POS(pos.first - 1, pos.second - 1));
                if (p->GetName() == "Pawn")
                {
                    return true;
                }
            }
            break;
    }
    //King Check
}


void Board::Move(POS start, POS end)
{
    Piece* p = board[start.first][start.second];
    NukeTile(end);
    p->Move(end);
    board[end.first][end.second] = p;
}

void Board::NukeTile(POS pos)
{
    if (board[pos.first][pos.second] != nullptr)
     {
        delete board[pos.first][pos.second];
        board[pos.first][pos.second] = nullptr;
    }
}

SquareState Board::CheckSquare(POS pos, Color color)
{
    if (pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7)
    {
        return SquareState::INVALID;
    }
    else if (board[pos.first][pos.second] == nullptr)
    {
        return SquareState::EMPTY;
    }
    else if (board[pos.first][pos.second]->GetColor() != color)
    {
        return SquareState::TAKEN_BY_ENEMY;
    }
    else if (board[pos.first][pos.second]->GetColor() == color)
    {
        return SquareState::TAKEN_BY_FRIENDLY;
    }
    else
    {
        //Should never reach here, compiler is crying
        return SquareState::INVALID;
    }
}

void Board::CreateBoard()
{
    for (int i = 0; i < 8; i++)
    {   
        board[1][i] = new Pawn(1, i, Color::BLACK);
        board[6][i] = new Pawn(6, i, Color::WHITE);
    }
    board[0][0] = new Rook(0, 0, Color::BLACK);
    board[0][7] = new Rook(0, 7, Color::BLACK);
    board[0][1] = new Knight(0, 1, Color::BLACK);
    board[0][6] = new Knight(0, 6, Color::BLACK);
    board[0][2] = new Bishop(0, 2, Color::BLACK);
    board[0][5] = new Bishop(0, 5, Color::BLACK);
    board[0][3] = new Queen(0, 3, Color::BLACK);
    board[0][4] = new King(0, 4, Color::BLACK);
    blackKing = board[0][4];

    board[7][0] = new Rook(7, 0, Color::WHITE);
    board[7][7] = new Rook(7, 7, Color::WHITE);
    board[7][1] = new Knight(7, 1, Color::WHITE);
    board[7][6] = new Knight(7, 6, Color::WHITE);
    board[7][2] = new Bishop(7, 2, Color::WHITE);
    board[7][5] = new Bishop(7, 5, Color::WHITE);
    board[7][3] = new Queen(7, 3, Color::WHITE);
    board[7][4] = new King(7, 4, Color::WHITE);
    whiteKing = board[7][4];
}

void Board::PrintBoard()
{   
    for (ROW row : board)
    {
        for (Piece* p : row)
        {
            if (p == nullptr)
            {
                cout << "0 ";
            }
            else
            {
                p->Info();
            }
        }
        cout << endl;
    }

}



Piece* Board::GetPiece(POS pos)
{
    return board[pos.first][pos.second];
}
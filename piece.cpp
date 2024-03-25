#include "piece.h"
#include "board.h"
#include <iostream>
#include <utility>
#include <vector>
#include <typeinfo>
#include <string>
using namespace std;

Piece::Piece(int in_row, int in_col, Color in_color)
{
    row = in_row;
    col = in_col;
    color = in_color;
}

void Piece::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    cout << "Moving to " << pos.first << ", " << pos.second << endl;
}

MOVES Piece::ValidMoves(Board &board)
{
    MOVES moves = {};
    for (POS dir : directions)
    {
        int r = row + dir.first;
        int c = col + dir.second;
        while (r >= 0 && r < 8 && c >= 0 && c < 8)
        {
            if (board.CheckSquare(make_pair(r, c), color) == SquareState::EMPTY)
            {
                cout << "Valid move: " << r << ", " << c << endl;
                moves.push_back(make_pair(r, c));
            }
            else if (board.CheckSquare(make_pair(r, c), color) == SquareState::TAKEN_BY_ENEMY)
            {
                cout << "Valid move: " << r << ", " << c << endl;
                moves.push_back(make_pair(r, c));
                break;
            }
            else if (board.CheckSquare(make_pair(r, c), color) == SquareState::TAKEN_BY_FRIENDLY)
            {
                break;
            }
            r += dir.first;
            c += dir.second;
        }
    }
    return moves;
}

Color Piece::GetColor()
{
    return color;
}
string Piece::GetName()
{
    string name = typeid(*this).name();
    name = name.substr(1);
    return name;
}

void Piece::Info()
{
    string color_name = "";
    switch (color)
    {
        case Color::WHITE:
            color_name = "White";
        case Color::BLACK:
            color_name = "Black";
    }
    cout << "<" << color_name << " " << GetName() << " at: " << row << ", " << col << ">";
}


Pawn::Pawn(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    firstMove = true;
}

void Pawn::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    firstMove = false;
    cout << "Moving pawn to " << pos.first << ", " << pos.second << endl;
}

MOVES Pawn::ValidMoves(Board &board)
{   
    MOVES moves = {};
    switch (color)
    {
        case Color::BLACK:
            if (board.CheckSquare(make_pair(row + 1, col), color) == SquareState::EMPTY)
            {
                moves.push_back(make_pair(row + 1, col));
                if (firstMove && board.CheckSquare(make_pair(row + 2, col), color) == SquareState::EMPTY)
                {
                    moves.push_back(make_pair(row + 2, col));
                }
            }
            if (board.CheckSquare(make_pair(row + 1, col + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(make_pair(row + 1, col + 1));
            }
            if (board.CheckSquare(make_pair(row + 1, col - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(make_pair(row + 1, col - 1));
            }
            break;
        case Color::WHITE:
            if (board.CheckSquare(make_pair(row - 1, col), color) == SquareState::EMPTY)
            {
                moves.push_back(make_pair(row - 1, col));
                if (firstMove && board.CheckSquare(make_pair(row - 2, col), color) == SquareState::EMPTY)
                {
                    moves.push_back(make_pair(row - 2, col));
                }
            }
            if (board.CheckSquare(make_pair(row - 1, col + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(make_pair(row - 1, col + 1));
            }
            if (board.CheckSquare(make_pair(row - 1, col - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(make_pair(row - 1, col - 1));
            }
            break;
    }
    return moves;
}



Rook::Rook(int in_row, int in_col, Color in_color) : Piece (in_row, in_col, in_color)
{
    firstMove = true;
    directions = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
}

void Rook::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    firstMove = false;
    cout << "Moving rook to " << pos.first << ", " << pos.second << endl;
}



Bishop::Bishop(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    directions = {make_pair(1, 1), make_pair(1, -1), make_pair(-1, 1), make_pair(-1, -1)};
}


Queen::Queen(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    directions = {make_pair(1, 1), make_pair(1, -1), make_pair(-1, 1), make_pair(-1, -1), make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
}


Knight::Knight(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color){}

MOVES Knight::ValidMoves(Board &board)
{
    MOVES moves = {};
    MOVES directions = {make_pair(2, 1), make_pair(2, -1), make_pair(-2, 1), make_pair(-2, -1), make_pair(1, 2), make_pair(1, -2), make_pair(-1, 2), make_pair(-1, -2)};
    for (POS dir : directions)
    {
        int r = row + dir.first;
        int c = col + dir.second;
        if (board.CheckSquare(make_pair(r, c), color) == SquareState::EMPTY)
        {
            //cout << "Valid move: " << r << ", " << c << endl;
            moves.push_back(make_pair(r, c));
        }
        else if (board.CheckSquare(make_pair(r, c), color) == SquareState::TAKEN_BY_ENEMY)
        {
            //cout << "Valid move: " << r << ", " << c << endl;
            moves.push_back(make_pair(r, c));
        }
    }
    return moves;
}



King::King(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    firstMove = true;
}

void King::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    firstMove = false;
    cout << "Moving king to " << pos.first << ", " << pos.second << endl;
}


MOVES King::ValidMoves(Board &board)
{
    MOVES moves = {};
    MOVES directions = {make_pair(1, 1), make_pair(1, -1), make_pair(-1, 1), make_pair(-1, -1), make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
    for (POS dir : directions)
    {
        int r = row + dir.first;
        int c = col + dir.second;
        if (board.CheckSquare(make_pair(r, c), color) == SquareState::EMPTY || board.CheckSquare(make_pair(r, c), color) == SquareState::TAKEN_BY_ENEMY)
        {
            //cout << "Valid move: " << r << ", " << c << endl;
            moves.push_back(make_pair(r, c));
        }
    }
    return moves;
}


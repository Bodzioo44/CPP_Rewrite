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
    std::cout << "Moving to " << pos.first << ", " << pos.second << std::endl;
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
                moves.push_back(make_pair(r, c));
            }
            else if (board.CheckSquare(make_pair(r, c), color) == SquareState::TAKEN_BY_ENEMY)
            {
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

POS Piece::GetPos()
{
    return make_pair(row, col);
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
    if (color == Color::WHITE) {color_name = "White";}
    else {color_name = "Black";}
    std::cout << "<" << color_name << " " << GetName() << " at: " << row << ", " << col << ">";
}

string Piece::GetPath()
{
    return path;
}

Piece::~Piece(){}


Pawn::Pawn(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    firstMove = true;
    AssignColorValues();
}

void Pawn::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    firstMove = false;
    std::cout << "Moving pawn to " << pos.first << ", " << pos.second << std::endl;
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


void Pawn::AssignColorValues()
{
    switch (color)
    {
        case Color::WHITE:
            path = "img/white_pawn.png";
            break;
        case Color::BLACK:
            path = "img/black_pawn.png";
            break;
    }

}


Rook::Rook(int in_row, int in_col, Color in_color) : Piece (in_row, in_col, in_color)
{
    firstMove = true;
    directions = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
    AssignColorValues();
}

void Rook::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    firstMove = false;
    std::cout << "Moving rook to " << pos.first << ", " << pos.second << std::endl;
}


void Rook::AssignColorValues()
{
    switch (color)
    {
        case Color::WHITE:
            path = "img/white_rook.png";
            break;
        case Color::BLACK:
            path = "img/black_rook.png";
            break;
    }
}


Bishop::Bishop(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    directions = {make_pair(1, 1), make_pair(1, -1), make_pair(-1, 1), make_pair(-1, -1)};
    AssignColorValues();
}


void Bishop::AssignColorValues()
{
    switch (color)
    {
        case Color::WHITE:
            path = "img/white_bishop.png";
            break;
        case Color::BLACK:
            path = "img/black_bishop.png";
            break;
    }
}

Queen::Queen(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    directions = {make_pair(1, 1), make_pair(1, -1), make_pair(-1, 1), make_pair(-1, -1), make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
    AssignColorValues();
}

void Queen::AssignColorValues()
{
    switch (color)
    {
        case Color::WHITE:
            path = "img/white_queen.png";
            break;
        case Color::BLACK:
            path = "img/black_queen.png";
            break;
    }
}

Knight::Knight(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    AssignColorValues();
}

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
            moves.push_back(make_pair(r, c));
        }
        else if (board.CheckSquare(make_pair(r, c), color) == SquareState::TAKEN_BY_ENEMY)
        {
            moves.push_back(make_pair(r, c));
        }
    }
    return moves;
}

void Knight::AssignColorValues()
{
    switch (color)
    {
        case Color::WHITE:
            path = "img/white_knight.png";
            break;
        case Color::BLACK:
            path = "img/black_knight.png";
            break;
    }
}


King::King(int in_row, int in_col, Color in_color) : Piece(in_row, in_col, in_color)
{
    firstMove = true;
    AssignColorValues();
}

void King::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    firstMove = false;
    std::cout << "Moving king to " << pos.first << ", " << pos.second << std::endl;
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
            moves.push_back(make_pair(r, c));
        }
    }
    return moves;
}

void King::AssignColorValues()
{
    switch (color)
    {
        case Color::WHITE:
            path = "img/white_king.png";
            break;
        case Color::BLACK:
            path = "img/black_king.png";
            break;
    }
}
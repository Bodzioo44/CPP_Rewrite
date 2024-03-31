#include "piece.h"
#include "board.h"
#include <iostream>
#include <utility>
#include <vector>
#include <typeinfo>
#include <string>

const MOVES Rook::directions = {POS(1, 0), POS(-1, 0), POS(0, 1), POS(0, -1)};
const MOVES Bishop::directions = {POS(1, 1), POS(1, -1), POS(-1, 1), POS(-1, -1)};
const MOVES Queen::directions = {POS(1, 1), POS(1, -1), POS(-1, 1), POS(-1, -1), POS(1, 0), POS(-1, 0), POS(0, 1), POS(0, -1)};

Piece::Piece(int in_row, int in_col, Color in_color)
{
    row = in_row;
    col = in_col;
    color = in_color;
    //cout << "piece directions: " << &directions << endl;
}

void Piece::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
}

MOVES Piece::EliminateInvalidMoves(Board &board, MOVES moves, POS pos)
{
    MOVES valid_moves = {};
    for (POS move : moves)
    {
        if (board.IsMoveValid(pos, move))
        {
            valid_moves.push_back(move);
        }
    }
    return valid_moves;
}

//FIXME add middle class for shared valid moves
MOVES Piece::GetMoves(){}

MOVES Piece::ValidMoves(Board &board)
{
    //std::cout << "shared valid mvoes" << std::endl;
    MOVES moves = {};
    //std::cout << "Inside Shared Valid_MOves" << &directions << std::endl;
    for (POS dir : GetMoves())
    {
        //std::cout <<"we got here" << endl;
        int r = row + dir.first;
        int c = col + dir.second;
        while (r >= 0 && r < 8 && c >= 0 && c < 8)
        {
            if (board.CheckSquare(POS(r, c), color) == SquareState::EMPTY)
            {
                moves.push_back(POS(r, c));
            }
            else if (board.CheckSquare(POS(r, c), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(r, c));
                break;
            }
            else if (board.CheckSquare(POS(r, c), color) == SquareState::TAKEN_BY_FRIENDLY)
            {
                break;
            }
            r += dir.first;
            c += dir.second;
        }
    }
    return EliminateInvalidMoves(board, moves, GetPos());
}

POS Piece::GetPos()
{
    return POS(row, col);
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

string Piece::Info()
{
    string color_name = "";
    if (color == Color::WHITE) {color_name = "White";}
    else {color_name = "Black";}
    return "<" + color_name + " " + GetName() + " at: " + std::to_string(row) + ", " + std::to_string(col) + ">";
}

string Piece::GetPath()
{
    return path;
}

Piece::~Piece()
{
    std::cout << "Absolutly obliterated" << std::endl;
}


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
}

MOVES Pawn::ValidMoves(Board &board)
{   
    MOVES moves = {};
    switch (color)
    {
        case Color::BLACK:
            if (board.CheckSquare(POS(row + 1, col), color) == SquareState::EMPTY)
            {
                moves.push_back(POS(row + 1, col));
                if (firstMove && board.CheckSquare(POS(row + 2, col), color) == SquareState::EMPTY)
                {
                    moves.push_back(POS(row + 2, col));
                }
            }
            if (board.CheckSquare(POS(row + 1, col + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row + 1, col + 1));
            }
            if (board.CheckSquare(POS(row + 1, col - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row + 1, col - 1));
            }
            break;
        case Color::WHITE:
            if (board.CheckSquare(POS(row - 1, col), color) == SquareState::EMPTY)
            {
                moves.push_back(POS(row - 1, col));
                if (firstMove && board.CheckSquare(POS(row - 2, col), color) == SquareState::EMPTY)
                {
                    moves.push_back(POS(row - 2, col));
                }
            }
            if (board.CheckSquare(POS(row - 1, col + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row - 1, col + 1));
            }
            if (board.CheckSquare(POS(row - 1, col - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row - 1, col - 1));
            }
            break;
    }
    return EliminateInvalidMoves(board, moves, GetPos());
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
    std::cout << "Inside ROok constructor: " << &directions << std::endl;  
    AssignColorValues();
}

MOVES Rook::GetMoves() {return directions;}

void Rook::Move(POS pos)
{
    row = pos.first;
    col = pos.second;
    firstMove = false;
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
    AssignColorValues();
}

MOVES Bishop::GetMoves() {return directions;}

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
    
    AssignColorValues();
}

MOVES Queen::GetMoves() {return directions;}

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
    MOVES directions = {POS(2, 1), POS(2, -1), POS(-2, 1), POS(-2, -1), POS(1, 2), POS(1, -2), POS(-1, 2), POS(-1, -2)};
    for (POS dir : directions)
    {
        int r = row + dir.first;
        int c = col + dir.second;
        if (board.CheckSquare(POS(r, c), color) == SquareState::EMPTY)
        {
            moves.push_back(POS(r, c));
        }
        else if (board.CheckSquare(POS(r, c), color) == SquareState::TAKEN_BY_ENEMY)
        {
            moves.push_back(POS(r, c));
        }
    }
    return EliminateInvalidMoves(board, moves, GetPos());
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
}

MOVES King::ValidMoves(Board &board)
{
    MOVES moves = {};
    MOVES directions = {POS(1, 1), POS(1, -1), POS(-1, 1), POS(-1, -1), POS(1, 0), POS(-1, 0), POS(0, 1), POS(0, -1)};
    for (POS dir : directions)
    {
        int r = row + dir.first;
        int c = col + dir.second;
        if (board.CheckSquare(POS(r, c), color) == SquareState::EMPTY || board.CheckSquare(POS(r, c), color) == SquareState::TAKEN_BY_ENEMY)
        {
            moves.push_back(POS(r, c));
        }
    }
    return EliminateInvalidMoves(board, moves, GetPos());
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
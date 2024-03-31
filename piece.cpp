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

Piece::Piece(Color in_color)
{
    color = in_color;
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
void Piece::FirstMove(){}

MOVES Piece::ValidMoves(Board &board, POS pos)
{
    int row = pos.first;
    int col = pos.second;
    MOVES moves = {};
    for (POS dir : GetMoves())
    {
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
    return EliminateInvalidMoves(board, moves, pos);
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
    return "<" + color_name + " " + GetName() + ">"; //+ std::to_string(row) + ", " + std::to_string(col) + ">";
}

string Piece::GetPath()
{
    return path;
}

Piece::~Piece()
{
    std::cout << "Absolutly obliterated" << std::endl;
}


Pawn::Pawn(Color in_color) : Piece(in_color)
{
    firstMove = true;
    AssignColorValues();
}


void Pawn::FirstMove()
{
    firstMove = false;

}

MOVES Pawn::ValidMoves(Board &board, POS pos)
{   
    int row = pos.first;
    int col = pos.second;
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
    return EliminateInvalidMoves(board, moves, pos);
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

Rook::Rook(Color in_color) : Piece (in_color)
{
    firstMove = true;
    AssignColorValues();
}


void Rook::FirstMove()
{
    firstMove = false;
}


MOVES Rook::GetMoves() {return directions;}


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

Bishop::Bishop(Color in_color) : Piece(in_color)
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

Queen::Queen(Color in_color) : Piece(in_color)
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

Knight::Knight(Color in_color) : Piece(in_color)
{
    AssignColorValues();
}

MOVES Knight::ValidMoves(Board &board, POS pos)
{
    int row = pos.first;
    int col = pos.second;
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
    return EliminateInvalidMoves(board, moves, pos);
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


King::King(Color in_color) : Piece(in_color)
{
    firstMove = true;
    AssignColorValues();
}

void King::FirstMove()
{
    firstMove = false;
}

MOVES King::ValidMoves(Board &board, POS pos)
{
    int row = pos.first;void FirstMove();
    int col = pos.second;
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
    return EliminateInvalidMoves(board, moves, pos);
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
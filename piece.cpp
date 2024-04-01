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

//Are these needed?
Piece::~Piece(){}
Pawn::~Pawn(){}
Rook::~Rook(){}
Bishop::~Bishop(){}
Queen::~Queen(){}
Knight::~Knight(){}
King::~King(){}

Piece::Piece(Color in_color)
{
    color = in_color;
}
Piece::Piece(const Piece &p): color(p.color), path(p.path) {}

MOVES Piece::EliminateInvalidMoves(Board &board, MOVES moves, POS pos) const
{
    MOVES valid_moves = {};
    for (POS move : moves)
    {
        if (board.IsMoveValid(pos, move, color))
        {
            valid_moves.push_back(move);
        }
    }
    return valid_moves;
}

// What to do with these?
MOVES Piece::GetDirections(){}
void Piece::FirstMove(){}

MOVES Piece::ValidMoves(Board &board, POS pos)
{
    int row = pos.first;
    int col = pos.second;
    MOVES moves = {};
    for (POS dir : GetDirections())
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

Color Piece::GetColor() const
{
    return color;
}
string Piece::GetName() const
{
    string name = typeid(*this).name();
    name = name.substr(1);
    return name;
}

string Piece::Info() const
{
    string color_name = "";
    if (color == Color::WHITE) {color_name = "White";}
    else {color_name = "Black";}
    return "<" + color_name + " " + GetName() + ">"; //+ std::to_string(row) + ", " + std::to_string(col) + ">";
}

string Piece::GetPath() const
{
    return path;
}



Pawn::Pawn(Color in_color) : Piece(in_color)
{
    firstMove = true;
    AssignColorValues();
}


Pawn::Pawn(const Pawn &p) : Piece(p), firstMove(p.firstMove){}

void Pawn::FirstMove()
{
    firstMove = false;
}

Pawn* Pawn::Clone()
{
    return new Pawn(*this);
}

MOVES Pawn::ValidMoves(Board &board, POS pos)
{   
    int row = pos.first;
    int col = pos.second;
    MOVES moves = {};
    switch (color)
    {
        case Color::BLACK:
            //forward
            if (board.CheckSquare(POS(row + 1, col), color) == SquareState::EMPTY)
            {
                moves.push_back(POS(row + 1, col));
                if (firstMove && board.CheckSquare(POS(row + 2, col), color) == SquareState::EMPTY)
                {
                    moves.push_back(POS(row + 2, col));
                }
            }
            //diagonal
            if (board.CheckSquare(POS(row + 1, col + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row + 1, col + 1));
            }
            if (board.CheckSquare(POS(row + 1, col - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row + 1, col - 1));
            }
            //en passant
            if (board.GetEnPassant() == POS(row, col + 1))
            {
                moves.push_back(POS(row + 1, col + 1));
            }

            if (board.GetEnPassant() == POS(row, col - 1))
            {
                moves.push_back(POS(row + 1, col - 1));
            }


            break;
        case Color::WHITE:
            // forward
            if (board.CheckSquare(POS(row - 1, col), color) == SquareState::EMPTY)
            {
                moves.push_back(POS(row - 1, col));
                if (firstMove && board.CheckSquare(POS(row - 2, col), color) == SquareState::EMPTY)
                {
                    moves.push_back(POS(row - 2, col));
                }
            }
            //diagonal
            if (board.CheckSquare(POS(row - 1, col + 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row - 1, col + 1));
            }
            if (board.CheckSquare(POS(row - 1, col - 1), color) == SquareState::TAKEN_BY_ENEMY)
            {
                moves.push_back(POS(row - 1, col - 1));
            }
            //en passant
            if (board.GetEnPassant() == POS(row, col + 1))
            {
                moves.push_back(POS(row - 1, col + 1));
            }

            if (board.GetEnPassant() == POS(row, col - 1))
            {
                moves.push_back(POS(row - 1, col - 1));
            }
            break;
    }
    return EliminateInvalidMoves(board, moves, pos);
}



bool Pawn::IsFirstMove() const
{
    return firstMove;
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


Rook::Rook(const Rook &r) : Piece(r), firstMove(r.firstMove){}

void Rook::FirstMove()
{
    firstMove = false;
}

Rook* Rook::Clone()
{
    return new Rook(*this);
}


MOVES Rook::GetDirections() {return directions;}


bool Rook::IsFirstMove() const
{
    return firstMove;
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

Bishop::Bishop(Color in_color) : Piece(in_color)
{
    AssignColorValues();
}

Bishop::Bishop(const Bishop &p) : Piece(p){}

Bishop* Bishop::Clone()
{
    return new Bishop(*this);
}

MOVES Bishop::GetDirections() {return directions;}

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

Queen::Queen(const Queen &q) : Piece(q){}

Queen* Queen::Clone()
{
    return new Queen(*this);
}


MOVES Queen::GetDirections() {return directions;}

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

Knight::Knight(Color in_color) : Piece(in_color) {AssignColorValues();}
Knight::Knight(const Knight &k) : Piece(k){}
Knight* Knight::Clone() {return new Knight(*this);}

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

King::King(const King &p) : Piece(p), firstMove(p.firstMove){}
King* King::Clone() {return new King(*this);}


void King::FirstMove()
{
    firstMove = false;
}

MOVES King::ValidMoves(Board &board, POS pos)
{
    int row = pos.first;
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
    if (firstMove)
    {
        if (board.CheckSquare(POS(row, col + 1), color) == SquareState::EMPTY && board.CheckSquare(POS(row, col + 2), color) == SquareState::EMPTY)
        {
            Piece* rook = board.GetPiece(POS(row, col + 3));
            if (rook != nullptr && rook->GetName() == "Rook" && dynamic_cast<Rook*>(rook)->IsFirstMove())
            {
                bool loop = true;
                for (int i = 0; i < 4; i++)
                {
                    if (board.IsSquareChecked(POS(row, col + i), color))
                    {
                        loop = false;
                        break;
                    }
                }
                if (loop) {moves.push_back(POS(row, 7));}
            }
        }
        if (board.CheckSquare(POS(row, col - 1), color) == SquareState::EMPTY && board.CheckSquare(POS(row, col - 2), color) == SquareState::EMPTY && board.CheckSquare(POS(row, col - 3), color) == SquareState::EMPTY)
        {
            Piece* rook = board.GetPiece(POS(row, col - 4));
            if (rook != nullptr && rook->GetName() == "Rook" && dynamic_cast<Rook*>(rook)->IsFirstMove())
            {
                bool loop = true;
                for (int i = 0; i < 5; i++)
                {
                    if (board.IsSquareChecked(POS(row, col - i), color))
                    {
                        loop = false;
                        break;
                    }
                }
                if (loop) {moves.push_back(POS(row, 0));}
            }
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

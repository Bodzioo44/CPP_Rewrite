#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <string>
using namespace std;
//TODO fix them imports
class Board;
//#define POS pair<int, int>
//#define MOVES vector<POS>
using POS = pair<int, int>;
using MOVES = vector<POS>;

enum class Color {WHITE, BLACK};


class Piece
{
public:
    Piece(int in_row, int in_col, Color in_color);
    virtual ~Piece();
    virtual void Move(POS pos);
    virtual MOVES ValidMoves(Board &board);
    virtual void AssignColorValues() = 0;
    POS GetPos();
    string GetName();
    Color GetColor();
    string GetPath();
    //TODO whats the difference between Info and AssignColorValues?;
    string Info();
protected:
    int row;
    int col;
    string path;
    Color color;
    MOVES directions;

};


class Pawn : public Piece
{
public:
    Pawn(int in_row, int in_col, Color in_color);
    MOVES ValidMoves(Board &board) override;
    void Move(POS pos) override;
    void AssignColorValues() override;
private:
    bool firstMove;
};

class Rook : public Piece
{
    public:
        Rook(int in_row, int in_col, Color in_color);
        void Move(POS pos) override;
        void AssignColorValues() override;
    private:
        bool firstMove;
        MOVES directions;
};

class Knight : public Piece
{
    public:
        Knight(int in_row, int in_col, Color in_color);
        MOVES ValidMoves(Board &board) override;
        void AssignColorValues() override;
};

class Bishop : public Piece
{
    public:
        Bishop(int in_row, int in_col, Color in_color);
        void AssignColorValues() override;
    private:
        MOVES directions;
};

class Queen : public Piece
{
    public:
        Queen(int in_row, int in_col, Color in_color);
        void AssignColorValues() override;
    private:
        MOVES directions;
};

class King : public Piece
{
    public:
        King(int in_row, int in_col, Color in_color);
        void Move(POS pos) override;
        MOVES ValidMoves(Board &board) override;
        void AssignColorValues() override;

    private:
        bool firstMove;
};


#endif
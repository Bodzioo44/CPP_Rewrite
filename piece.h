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
    Piece(Color in_color);
    virtual ~Piece();
    virtual MOVES ValidMoves(Board &board, POS pos);
    virtual MOVES GetMoves();
    virtual void AssignColorValues() = 0;
    virtual void FirstMove();
    MOVES EliminateInvalidMoves(Board &board, MOVES moves, POS pos);
    string GetName();
    Color GetColor();
    string GetPath();
    //TODO whats the difference between Info and AssignColorValues?;
    string Info();
protected:
    string path;
    Color color;
    const static MOVES directions;

};


class Pawn : public Piece
{
public:
    Pawn(Color in_color);
    MOVES ValidMoves(Board &board, POS pos) override;
    void FirstMove();
    void AssignColorValues() override;
private:
    bool firstMove;
};

class Rook : public Piece
{
    public:
        Rook(Color in_color);
        MOVES GetMoves() override;
        void FirstMove();
        void AssignColorValues() override;
    private:
        bool firstMove;
        const static MOVES directions;
};

class Knight : public Piece
{
    public:
        Knight(Color in_color);
        MOVES ValidMoves(Board &board, POS pos) override;
        void AssignColorValues() override;
};

class Bishop : public Piece
{
    public:
        Bishop(Color in_color);
        MOVES GetMoves() override;
        void AssignColorValues() override;
    private:
        const static MOVES directions;
};

class Queen : public Piece
{
    public:
        Queen(Color in_color);
        MOVES GetMoves() override;
        void AssignColorValues() override;
    private:
        const static MOVES directions;
};

class King : public Piece
{
    public:
        King(Color in_color);
        MOVES ValidMoves(Board &board, POS pos) override;
        void FirstMove();
        void AssignColorValues() override;

    private:
        bool firstMove;
};


#endif
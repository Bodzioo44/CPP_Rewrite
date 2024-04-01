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
    Piece(const Piece &piece);
    virtual ~Piece();
    virtual Piece* Clone() = 0;
    virtual MOVES ValidMoves(Board &board, POS pos);
    virtual MOVES GetMoves();
    virtual void AssignColorValues() = 0;
    virtual void FirstMove();
    MOVES EliminateInvalidMoves(Board &board, MOVES moves, POS pos);
    string GetName();
    Color GetColor();
    string GetPath();
    string Info();
protected:
    Color color;
    string path;
    const static MOVES directions;

};


class Pawn : public Piece
{
public:
    Pawn(Color in_color);
    Pawn(const Pawn &p);
    ~Pawn() override;

    Pawn* Clone() override;
    MOVES ValidMoves(Board &board, POS pos) override;
    void FirstMove();
    bool IsFirstMove() const;
    void AssignColorValues() override;
private:
    bool firstMove;
};

class Rook : public Piece
{
    public:
        Rook(Color in_color);
        Rook(const Rook &r);
        ~Rook() override;
        Rook* Clone() override;
        MOVES GetMoves() override;
        void FirstMove();
        bool IsFirstMove();
        void AssignColorValues() override;
    private:
        bool firstMove;
        const static MOVES directions;

};

class Knight : public Piece
{
    public:
        Knight(Color in_color);
        Knight(const Knight &p);
        ~Knight() override;
        Knight* Clone() override;
        MOVES ValidMoves(Board &board, POS pos) override;
        void AssignColorValues() override;
};

class Bishop : public Piece
{
    public:
        Bishop(Color in_color);
        Bishop(const Bishop &p);
        ~Bishop() override;
        Bishop* Clone() override;
        MOVES GetMoves() override;
        void AssignColorValues() override;
    private:
        const static MOVES directions;
};

class Queen : public Piece
{
    public:
        Queen(Color in_color);
        Queen(const Queen &q);
        ~Queen() override;
        Queen* Clone() override;
        MOVES GetMoves() override;
        void AssignColorValues() override;
    private:
        const static MOVES directions;
};

class King : public Piece
{
    public:
        King(Color in_color);
        King(const King &k);
        ~King() override;
        King* Clone() override;
        MOVES ValidMoves(Board &board, POS pos) override;
        void FirstMove();
        void AssignColorValues() override;

    private:
        bool firstMove;
};


#endif
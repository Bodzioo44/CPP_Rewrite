#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <string>

#include "Include/enums.h"

using namespace std;
using POS = pair<int, int>;
using MOVES = vector<POS>;
using Color = Enums::Color;

class Board;

class Piece
{
public: 
    Piece(Color in_color);
    Piece(const Piece &piece);
    virtual ~Piece();

    virtual Piece* Clone() = 0; //Deep copies the piece, and returns the pointer to it
    virtual MOVES ValidMoves(Board &board, POS pos); //Returns the valid moves of the piece (using board methods)

    virtual void FirstMove(); //Sets piece's bool firstMove to false (used by pawn, rook, king)
    
    string GetName() const; //Returns the name of the piece
    Color GetColor() const; //Returns the color of the piece
    string GetPath() const; //Returns the path to the image of the piece
    string Info() const; //Returns the name of the piece and its color (for debugging)
protected:
    virtual MOVES GetDirections(); //Returns directions in which the piece can move (used by bishop, rook, queen) 
    //since ValidMoves is non pure virtual method, it would reach to base direction attribute instead of derived class's direction attribute?
    //thats why separate GetDirections method is used?

    MOVES EliminateInvalidMoves(Board &board, MOVES moves, POS pos) const; //Eliminates the moves that are invalid (using board methods)
    virtual void AssignColorValues() = 0; //Assigns the color specific values to the piece
    Color color; //Color of the piece
    string path; //Path to the image of the piece
    const static MOVES directions; //Directions in which pieces can move (used by bishop, rook, queen)
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
    
private:
    void AssignColorValues() override;
    bool firstMove;
};

class Rook : public Piece
{
    public:
        Rook(Color in_color);
        Rook(const Rook &r);
        ~Rook() override;
        Rook* Clone() override;

        bool IsFirstMove() const;
        void FirstMove();


    private:
        void AssignColorValues() override;
        const static MOVES directions;
        MOVES GetDirections() override;
        bool firstMove;

};

class Knight : public Piece
{
    public:
        Knight(Color in_color);
        Knight(const Knight &p);
        ~Knight() override;
        Knight* Clone() override;
        MOVES ValidMoves(Board &board, POS pos) override;
    private:
        void AssignColorValues() override;
};

class Bishop : public Piece
{
    public:
        Bishop(Color in_color);
        Bishop(const Bishop &p);
        ~Bishop() override;
        Bishop* Clone() override;

    private:
        const static MOVES directions;
        void AssignColorValues() override;
        MOVES GetDirections() override;
};

class Queen : public Piece
{
    public:
        Queen(Color in_color);
        Queen(const Queen &q);
        ~Queen() override;
        Queen* Clone() override;

    private:
        const static MOVES directions;
        MOVES GetDirections() override;
        void AssignColorValues() override;
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
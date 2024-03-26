#include <iostream>
#include "board.h"
#include <QString>

#include "QtDesigner.h"
using namespace std;


void print(auto x);

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QMainWindow mainWindow;
    Ui::MainWindow window;
    window.setupUi(&mainWindow);
    mainWindow.show();
    return app.exec();

    Board b;
    while (true)
    {
        int row, col;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter col: ";
        cin >> col;
        POS pos = make_pair(row, col);
        cout << "grabbing piece at " << row << ", " << col << endl;
        Piece* p = b.GetPiece(pos);
        if (p != nullptr)
        {
            p->Info();
            cout << endl;
            MOVES moves = p->ValidMoves(b);
            for (POS move : moves)
            {
                cout << "Valid move: " << move.first << ", " << move.second << endl;
            }
        }
        else
        {
            cout << "No piece at " << row << ", " << col << endl;
        }
    }
    
    return 0;
}



void print(auto x)
{
    for (auto i : x)
    {
        cout << i << " ";
    }
    cout << endl;
}
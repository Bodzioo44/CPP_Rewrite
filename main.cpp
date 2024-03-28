#include <iostream>
#include "board.h"
#include <QString>
#include <QApplication>
#include <QPushButton>

#include "QtDesigner.h"
#include "MainWindow.cpp"
using namespace std;


#include <QImage>

int main(int argc, char *argv[])
{
    cout << "Hello World" << endl;
    QApplication app(argc, argv);
    //Create main window
    MainWindow window;
    window.show();
    return app.exec();

    cout << "blyat" << endl;

    Board b;
    while (true)
    {
        //app.processEvents();
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

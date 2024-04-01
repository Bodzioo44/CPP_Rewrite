#include <iostream>
#include <QString>
#include <QApplication>
#include <QPushButton>

#include "Qt/ui_QtDesigner.h"
#include "Qt/MainWindow.cpp"
using namespace std;


#include <QImage>

int main(int argc, char *argv[])
{
    
    cout << "Hello World" << endl;
    cout << "blyat" << endl;
    QApplication app(argc, argv);
    //Create main window
    MainWindow window;
    window.show();
    return app.exec();


    
    return 0;
}

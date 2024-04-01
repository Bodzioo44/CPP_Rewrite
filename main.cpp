#include <QApplication>
#include "Qt/MainWindow.cpp"

#include <iostream>
using namespace std;


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

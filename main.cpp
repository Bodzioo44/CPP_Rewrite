#include <QtWidgets/QApplication>
#include "Qt/MainWindow.cpp"

#include <iostream>
using namespace std;



#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QFile>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();

    // QJsonObject Game_Update;
    // Game_Update["type"] = "Normal";
    // Game_Update["fromX"] = 1;
    // Game_Update["fromY"] = 3;

    // QJsonDocument doc(Game_Update);
    // cout << doc.toJson().toStdString() << endl;
    // for (auto key: Game_Update.keys())
    // {
    //     cout << typeid(key).name() << endl;
    //     cout << typeid(Game_Update[key]).name() << endl;
    //     cout << key.toStdString() << " " << Game_Update[key].toInt() << endl;
    // }


    // return 0;

}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Qt/ui_QtDesigner.h"
#include "Qt/GameWidget.cpp"
#include <QMainWindow>
#include <QObject>



class MainWindow : public Ui::MainWindow, public QMainWindow
{
    //Q_OBJECT
public:
    MainWindow();

private:
    void Online_Button_Action();
    void Offline_Button_Action();
    void Create_Lobby_Button_Action();
    void Join_Lobby_Button_Action();
    void Update_Lobby_List_Button_Action();
};


#endif
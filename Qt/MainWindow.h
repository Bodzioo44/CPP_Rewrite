#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_QtDesigner.h"
#include "Qt/GameWidget.h"
#include "Include/enums.h"
//#include "Include/Get_Api_Json.h"


#include <QtNetwork/QTcpSocket>
#include <QtWidgets/QMainWindow>
#include <QtCore/QObject>


#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QFile>

#include <iostream>
using namespace std;





class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();
        void Message_Handler();
        void Disconnected();
        void SendData(QJsonObject json);

    public slots:
        void Received_Game_Update(QJsonObject jsonMessage);

    private:
        void Message_Input_Action();
        //Connection Page
        void Online_Button_Action();
        void Offline_Button_Action();
        //Lobby List Page
        void Create_Lobby_Button_Action();
        void Join_Lobby_Button_Action();
        void Update_Lobby_List_Button_Action();
        //Lobby Creation Page
        void Checkers_2_Button_Action();
        void Chess_2_Button_Action();
        void Chess_4_Button_Action();
        void Exit_Lobby_Creation_Button_Action();
        //Lobby Page
        void Leave_Lobby_Button_Action();
        void Start_Lobby_Button_Action();
        void Kick_Player_Button_Action();

        void Set_Lobby_List_Tree(QJsonObject);
        void Set_Lobby_Info_Tree(QJsonObject);


        QTcpSocket* socket;
        GameWidget* game_widget;

        QString Int_to_String(int i);
};


#endif
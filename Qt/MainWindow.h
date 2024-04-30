#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_QtDesigner.h"
#include "Qt/GameWidget.h"
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



const QString JOIN_LOBBY = "Join_Lobby";
const QString CREATE_LOBBY = "Create_Lobby";
const QString LEAVE_LOBBY = "Leave_Lobby";
const QString REQUEST_LOBBY_LIST = "Request_Lobby_List";
const QString UPDATE_LOBBY_LIST = "Update_Lobby";
const QString KICK_PLAYER = "Kick_Player";  
const QString START_LOBBY = "Start_Lobby";
const QString MESSAGE = "Message";
const QString LOBBY_MESSAGE = "Lobby_Message";
const QString GLOBAL_MESSAGE = "Global_Message";
const QString GAME_UPDATE = "Game_Update";


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


        QTcpSocket* socket;
        GameWidget* game_widget;
};


#endif
#include "Qt/MainWindow.h"

MainWindow::MainWindow()
{
    setupUi(this);
    setCentralWidget(gridLayoutWidget);

    Global_Chat_Tab->setLayout(Global_Chat_Tab_Layout);
    Lobby_Chat_Tab->setLayout(Lobby_Chat_Tab_Layout);

    Connection_Page->setLayout(Connection_Page_Layout);
    Lobby_List_Page->setLayout(Lobby_List_Page_Layout);
    Lobby_Creation_Page->setLayout(Lobby_Creation_Layout); 
    Lobby_Info_Page->setLayout(Lobby_Info_Page_Layout);
    Game_Page->setLayout(Game_Page_Layout);

    //IP_Input_Box->setText("Bodzioo44.ddns.net");
    IP_Input_Box->setText("127.0.0.1");
    Name_Input_Box->setText("Player1");

    //Chat Box
    connect(Message_Input_Box, &QLineEdit::returnPressed, this, &MainWindow::Message_Input_Action);
    //Connection Page
    connect(Online_Button, &QPushButton::clicked, this, &MainWindow::Online_Button_Action); 
    connect(Offline_Button, &QPushButton::clicked, this, &MainWindow::Offline_Button_Action);
    //Lobby List Page
    connect(Create_Lobby_Button, &QPushButton::clicked, this, &MainWindow::Create_Lobby_Button_Action);
    connect(Join_Lobby_Button, &QPushButton::clicked, this, &MainWindow::Join_Lobby_Button_Action);
    connect(Update_Lobby_List_Button, &QPushButton::clicked, this, &MainWindow::Update_Lobby_List_Button_Action);
    //Lobby Creation Page
    connect(Checkers_2_Button, &QPushButton::clicked, this, &MainWindow::Checkers_2_Button_Action);
    connect(Chess_2_Button, &QPushButton::clicked, this, &MainWindow::Chess_2_Button_Action);
    connect(Chess_4_Button, &QPushButton::clicked, this, &MainWindow::Chess_4_Button_Action);
    connect(Exit_Lobby_Creation_Button, &QPushButton::clicked, this, &MainWindow::Exit_Lobby_Creation_Button_Action);
    //Lobby Page
    connect(Leave_Lobby_Button, &QPushButton::clicked, this, &MainWindow::Leave_Lobby_Button_Action);
    connect(Start_Lobby_Button, &QPushButton::clicked, this, &MainWindow::Start_Lobby_Button_Action);
    connect(Kick_Player_Button, &QPushButton::clicked, this, &MainWindow::Kick_Player_Button_Action);

    //QTcpSocket stuff
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::Message_Handler);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::Disconnected);
    
    // QFile API_Calls("Include/API_Calls.json");
    // API_Calls.open(QIODevice::ReadOnly | QIODevice::Text);
    // QString raw_api_calls;
    // raw_api_calls = API_Calls.readAll();
    // API_Calls.close();
    // //cout << raw_api_calls.toStdString() << endl;
    // QJsonDocument Json_api_calls = QJsonDocument::fromJson(raw_api_calls.toUtf8());
    // cout << Json_api_calls.toJson().toStdString() << endl;
    // QJsonObject json_api_calls = Json_api_calls.object();
    // for (auto key : json_api_calls.keys())
    // {
    //     QJsonValue val = json_api_calls[key];
    //     if (key == "Game_Update")
    //     {
    //         cout << val["type"].toString().toStdString() << endl;
    //     }
    // }
    //QJsonObject API_Calls = Get_Api_Json_Obj();


}

MainWindow::~MainWindow()
{
    delete socket;
}


void MainWindow::Received_Game_Update(QJsonObject jsonMessage)
{
    cout << "Received Game Update!" << endl;

    QJsonObject jsonMessageAPI;
    jsonMessageAPI[GAME_UPDATE] = jsonMessage;
    SendData(jsonMessageAPI);

}

/////////////////////////////////
//QTcpSocket STUFF (SEND/RECEIVE)
/////////////////////////////////

void MainWindow::Message_Handler()
{
    QByteArray data = socket->readAll(); //receive raw string from server
    QJsonDocument doc = QJsonDocument::fromJson(data); //serialize it to json document
    QJsonObject json = doc.object(); //get the json object
    QString strJson(doc.toJson(QJsonDocument::Indented)); //convert it to string
    cout << "Received: " << strJson.toStdString() << endl;
}

void MainWindow::SendData(QJsonObject json)
{
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    cout << "Sending: " << data.toStdString() << endl;
    socket->write(data);
}

void MainWindow::Disconnected()
{
    cout << "Disconnected from the server!" << endl;
    Stacked_Widget->setCurrentWidget(Connection_Page);
}

/////////////////   
//CONNECTION PAGE
/////////////////

void MainWindow::Online_Button_Action()
{
    socket->connectToHost(IP_Input_Box->text(), 4444);
    if (socket->waitForConnected(5000))
    {
        cout << "Connected!" << endl;
        Stacked_Widget->setCurrentWidget(Lobby_List_Page);
    }
    else
    {
        cout << "Failed to connect! Check if Ip is correct!" << endl;
    }
    Stacked_Widget->setCurrentWidget(Connection_Page);
}

void MainWindow::Offline_Button_Action()
{   
    Stacked_Widget->setCurrentWidget(Game_Page);
    game_widget = new GameWidget();
    game_widget->SetGame(GameType::CHESS_2, Color::WHITE);
    Game_Page_Layout->addWidget(game_widget);
    connect(game_widget, &GameWidget::MoveMade, this, &MainWindow::Received_Game_Update);
}


/////////////////
//LOBBY LIST PAGE
/////////////////


void MainWindow::Create_Lobby_Button_Action()
{
    std::cout << "Create Lobby Button Pressed" << std::endl;
    Stacked_Widget->setCurrentWidget(Lobby_Creation_Page);
}

void MainWindow::Join_Lobby_Button_Action()
{
    QList<QTreeWidgetItem*> selectedItems = Lobby_List_Tree_Widget->selectedItems();
    if (!selectedItems.isEmpty())
    {
        int lobby_id = selectedItems[0]->text(0).toInt();
        QJsonObject jsonMessage {{JOIN_LOBBY, lobby_id}};
        SendData(jsonMessage);
    }
    else
    {
        cout << "No lobby selected!" << endl;
    }
}

void MainWindow::Update_Lobby_List_Button_Action()
{
    QJsonObject jsonMessage {{REQUEST_LOBBY_LIST, "0"}};
    SendData(jsonMessage);
    std::cout << "Update Lobby List Button Pressed" << std::endl;
}

/////////////////////
//LOBBY CREATION PAGE
/////////////////////

void MainWindow::Checkers_2_Button_Action()
{
    QJsonObject jsonMessage {{CREATE_LOBBY, (int)GameType::CHECKERS_2}};
    SendData(jsonMessage);
    std::cout << "Checkers 2 Button Pressed" << std::endl;
}

void MainWindow::Chess_2_Button_Action()
{
    QJsonObject jsonMessage {{CREATE_LOBBY, (int)GameType::CHESS_2}};
    SendData(jsonMessage);
    std::cout << "Chess 2 Button Pressed" << std::endl;
}

void MainWindow::Chess_4_Button_Action()
{
    QJsonObject jsonMessage {{CREATE_LOBBY, (int)GameType::CHESS_4}};
    SendData(jsonMessage);
    std::cout << "Chess 4 Button Pressed" << std::endl;
}

void MainWindow::Exit_Lobby_Creation_Button_Action()
{
    std::cout << "Exit Lobby Creation Button Pressed" << std::endl;
    Stacked_Widget->setCurrentWidget(Lobby_List_Page);
}

////////////
//LOBBY PAGE
////////////

void MainWindow::Leave_Lobby_Button_Action()
{
    QJsonObject jsonMessage {{LEAVE_LOBBY, "0"}};
    SendData(jsonMessage);
    std::cout << "Leave Lobby Button Pressed" << std::endl;
}

void MainWindow::Start_Lobby_Button_Action()
{
    QJsonObject jsonMessage {{START_LOBBY, "0"}};
    SendData(jsonMessage);
    std::cout << "Start Lobby Button Pressed" << std::endl;
}

void MainWindow::Kick_Player_Button_Action()
{
    QList<QTreeWidgetItem*> selectedItems = Lobby_Info_Tree_Widget->selectedItems();
    if (!selectedItems.isEmpty())
    {
        int player_name = selectedItems[0]->text(0).toInt();
        QJsonObject jsonMessage {{KICK_PLAYER, player_name}};
        SendData(jsonMessage);
    }
    else
    {
        cout << "No player selected!" << endl;
    }
    std::cout << "Kick Player Button Pressed" << std::endl;
}


/////////////
//Message Box
/////////////

void MainWindow::Message_Input_Action()
{
    QString message = Message_Input_Box->text();
    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        cout << "Not connected to the server!" << endl;
    }
    else if (!message.isEmpty())
    {
        //cout << "problem inside check" << endl;
        QWidget* current_widget = Chat_Tab_Widget->currentWidget();
        if (current_widget == Global_Chat_Tab)
        {
            QJsonObject jsonMessage {{GLOBAL_MESSAGE, message}};
            cout << "Sending: " << endl;
            SendData(jsonMessage);
        }
        else if (current_widget == Lobby_Chat_Tab)
        {
            QJsonObject jsonMessage {{LOBBY_MESSAGE, message}};
            //cout << "Sending: " << endl;
            SendData(jsonMessage);
        }
    }
    else
    {
        cout << "Message is empty!" << endl;
    }
}
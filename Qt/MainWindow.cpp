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

    IP_Input_Box->setText("Bodzioo44.ddns.net");
    //IP_Input_Box->setText("127.0.0.1");
    Name_Input_Box->setText("Player");

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

    //Game Stuff
    game_widget = new GameWidget(this);
    Game_Page_Layout->addWidget(game_widget);
    connect(game_widget, &GameWidget::MoveMade, this, &MainWindow::Received_Game_Update);
}

MainWindow::~MainWindow()
{

    //apparently QTcpSocket doesnt inherit form QWidget, and because of that it doesnt get deleted alongside parent?
    //doesnt seem right? anyway, deleting the socket here prevents Segmentation fault (core dumped) while closing the app
    delete socket;
    //delete game_widget;
    //socket and game_widget should auto delete themselves when the parent is deleted

}


void MainWindow::Received_Game_Update(QJsonObject jsonMessage)
{
    cout << "Received Game Update!" << endl;

    QJsonObject jsonMessageAPI;
    jsonMessageAPI[API::GAME_UPDATE] = jsonMessage;
    SendData(jsonMessageAPI);

}

/////////////////////////////////
//QTcpSocket STUFF (SEND/RECEIVE)
/////////////////////////////////

void MainWindow::Message_Handler()
{
    QByteArray data = socket->readAll(); //receive raw string from the socket
    QJsonDocument doc = QJsonDocument::fromJson(data); //serialize it to a doc
    QJsonObject json = doc.object(); //get the json object

    QString strJson(doc.toJson(QJsonDocument::Indented)); //convert it to string
    cout << "Received: " << strJson.toStdString() << endl; //print it out for debugging

    for (QJsonObject::const_iterator it = json.begin(); it != json.end(); ++it)
    {
        QString key = it.key();

        if (key == API::CREATE_LOBBY)
        {
            Stacked_Widget->setCurrentWidget(Lobby_Info_Page);
            QJsonObject value = it.value().toObject();
            Set_Lobby_Info_Tree(value);

        }
        else if (key == API::JOIN_LOBBY)
        {
            Stacked_Widget->setCurrentWidget(Lobby_Info_Page);
            QJsonObject value = it.value().toObject();
            Set_Lobby_Info_Tree(value);
        }
        else if (key == API::LEAVE_LOBBY)
        {
            Stacked_Widget->setCurrentWidget(Lobby_List_Page);
            Update_Lobby_List_Button_Action();  
        
        }
        else if (key == API::UPDATE_LOBBY)
        {
            cout << "inside update lobby key";
            QJsonObject value = it.value().toObject();
            Set_Lobby_Info_Tree(value);
        }
        else if (key == API::GAME_UPDATE)
        {
            cout << "inside game update key" << endl;
            game_widget->ReceiveUpdate(it.value().toObject());
        }
        else if (key == API::GAME_HISTORY)
        {
            Stacked_Widget->setCurrentWidget(Game_Page);
            for (QJsonValue value : it.value().toArray())
            {
                game_widget->ReceiveUpdate(value.toObject());
                //QThread::msleep(1000);

            }
        }
        else if (key == API::RECONNECT)
        {
            int Start_Lobby = it.value().toObject()[API::START_LOBBY].toInt();
            QJsonArray Game_History = it.value().toObject()[API::GAME_HISTORY].toArray();

            Stacked_Widget->setCurrentWidget(Game_Page);
            game_widget->SetGame(GameType::CHESS_2, static_cast<Color>(Start_Lobby));

            for (QJsonValue value : Game_History)
            {
                game_widget->ReceiveUpdate(value.toObject());
                QThread::msleep(1000);

            }

        }
        else if (key == API::MESSAGE)
        {
            QJsonArray value = it.value().toArray();
            for (auto i : value)
            {
                cout << i.toString().toStdString() << endl;
            }
        }
        else if (key == API::UPDATE_LOBBY_LIST)
        {
            QJsonObject value = it.value().toObject();
            Set_Lobby_List_Tree(value);
        }
        
        // else if (key == API::DISCONNECT)
        // {
        //     cout << "Disconnected from the server!" << endl;
        //     Stacked_Widget->setCurrentWidget(Connection_Page);
        // }
        else if (key == API::START_LOBBY)
        {
            //cout << "Game has started!" << endl;
            Stacked_Widget->setCurrentWidget(Game_Page);
            game_widget->SetGame(GameType::CHESS_2, static_cast<Color>(it.value().toInt()));
        }

        else if (key == API::GLOBAL_MESSAGE)
        {
            Global_Chat_Text_Edit->append(it.value().toString());
            Message_Input_Box->clear();
        }
        else if (key == API::LOBBY_MESSAGE)
        {
            Lobby_Chat_Text_Edit->append(it.value().toString());
            Message_Input_Box->clear();
        }

        else
        {
            cout << "Unknown API call: " << key.toStdString() << endl;
        }
    }


}

void MainWindow::SendData(QJsonObject json)
{
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    cout << "Sending: " << data.toStdString() << "With length of: " << std::size(data) << endl;
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
        cout << "Succesfully connected to the server!" << endl;
        SendData(QJsonObject{{API::ASSIGN_NAME, Name_Input_Box->text()}});
        //FIXME: Wait for confirmation? to avoid screen flickering on disconnect.
        //Also rerequest data after disconnect.
        Stacked_Widget->setCurrentWidget(Lobby_List_Page);
        Lobby_List_Tree_Widget->clear();   

    }
    else
    {
        cout << "Failed to connect! Check if Ip is correct!" << endl;
    }
    //Stacked_Widget->setCurrentWidget(Connection_Page);
    //Stacked_Widget->setCurrentWidget(Lobby_List_Page);
}

void MainWindow::Offline_Button_Action()
{   
    //Stacked_Widget->setCurrentWidget(Game_Page);
    //game_widget->SetGame(GameType::CHESS_2, Color::WHITE);
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
        QJsonObject jsonMessage {{API::JOIN_LOBBY, lobby_id}};
        SendData(jsonMessage);
    }
    else
    {
        cout << "No lobby selected!" << endl;
    }
}

void MainWindow::Update_Lobby_List_Button_Action()
{
    QJsonObject jsonMessage {{API::REQUEST_LOBBY_LIST, "0"}};
    SendData(jsonMessage);
    std::cout << "Update Lobby List Button Pressed" << std::endl;
}

/////////////////////
//LOBBY CREATION PAGE
/////////////////////

void MainWindow::Checkers_2_Button_Action()
{
    QJsonObject jsonMessage {{API::CREATE_LOBBY, (int)GameType::CHECKERS_2}};
    SendData(jsonMessage);
    std::cout << "Checkers 2 Button Pressed" << std::endl;
}

void MainWindow::Chess_2_Button_Action()
{
    QJsonObject jsonMessage {{API::CREATE_LOBBY, (int)GameType::CHESS_2}};
    SendData(jsonMessage);
    std::cout << "Chess 2 Button Pressed" << std::endl;
}

void MainWindow::Chess_4_Button_Action()
{
    QJsonObject jsonMessage {{API::CREATE_LOBBY, (int)GameType::CHESS_4}};
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
    QJsonObject jsonMessage {{API::LEAVE_LOBBY, "0"}};
    SendData(jsonMessage);
    std::cout << "Leave Lobby Button Pressed" << std::endl;
}

void MainWindow::Start_Lobby_Button_Action()
{
    QJsonObject jsonMessage {{API::START_LOBBY, "0"}};
    SendData(jsonMessage);
    std::cout << "Start Lobby Button Pressed" << std::endl;
}

void MainWindow::Kick_Player_Button_Action()
{
    QList<QTreeWidgetItem*> selectedItems = Lobby_Info_Tree_Widget->selectedItems();
    if (!selectedItems.isEmpty())
    {
        int player_name = selectedItems[0]->text(0).toInt();
        QJsonObject jsonMessage {{API::KICK_PLAYER, player_name}};
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
            QJsonObject jsonMessage {{API::GLOBAL_MESSAGE, message}};
            cout << "Sending: " << endl;
            SendData(jsonMessage);
        }
        else if (current_widget == Lobby_Chat_Tab)
        {
            QJsonObject jsonMessage {{API::LOBBY_MESSAGE, message}};
            //cout << "Sending: " << endl;
            SendData(jsonMessage);
        }
    }
    else
    {
        cout << "Message is empty!" << endl;
    }
}



void MainWindow::Set_Lobby_List_Tree(QJsonObject json)
{
    Lobby_List_Tree_Widget->clear();   

    for (auto key : json.keys())
    {
        QTreeWidgetItem* header = new QTreeWidgetItem();

        header->setText(0, key);
        QJsonObject lobby_info = json[key].toObject();

        //TODO: Replace "Player" section with fancy custom widget that can actually display all the players?
        header->setText(1, QString::number(lobby_info["Slots"].toInt()));
        header->setText(2, lobby_info["GameType"].toString());
        header->setText(3, lobby_info["Status"].toBool() ? "Game has already started." : "Waiting for more players"); 

        Lobby_List_Tree_Widget->addTopLevelItem(header);
    }
}

void MainWindow::Set_Lobby_Info_Tree(QJsonObject json)
{
    Lobby_Info_Tree_Widget->clear();

    //json["Slots"] = 2;
    Lobby_Players_Label->setText("Max Players: " + QString::number(json["Slots"].toInt()));
    cout << typeid(json["Slots"]).name() << endl;
    Lobby_Type_Label->setText("Type: " + json["GameType"].toString());
    Lobby_ID_Label->setText("Lobby ID: " + QString::number(json["Lobby_ID"].toInt()));
    
    //json["Players"]["Player1"] = ["Player1", "White"]

    for (auto key : json["Players"].toObject().keys()) //each iteration is one player/one slot
    {
        QTreeWidgetItem* header = new QTreeWidgetItem(); //this one gets auto deleted when parent is deleted or cleared

        QJsonArray value = json["Players"].toObject()[key].toArray();
        header->setText(0, value[0].toString());
        header->setText(1, Int_to_String(value[1].toInt()));

        Lobby_Info_Tree_Widget->addTopLevelItem(header);
    }
}

//is there a better way to convert enum to string? map?
QString MainWindow::Int_to_String(int i)
{
    switch(i)
    {
        case 0: return "White";
        case 1: return  "Black";
        case 2: return "Red";
        case 3: return "Blue";
        default: return "Compiler is crying";
    }
}
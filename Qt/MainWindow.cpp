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

    connect(Online_Button, &QPushButton::clicked, this, &MainWindow::Online_Button_Action); 
    connect(Offline_Button, &QPushButton::clicked, this, &MainWindow::Offline_Button_Action);
    connect(Create_Lobby_Button, &QPushButton::clicked, this, &MainWindow::Create_Lobby_Button_Action);
    connect(Join_Lobby_Button, &QPushButton::clicked, this, &MainWindow::Join_Lobby_Button_Action);
    connect(Update_Lobby_List_Button, &QPushButton::clicked, this, &MainWindow::Update_Lobby_List_Button_Action);
    SocketTest();
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::Received);

}


void MainWindow::Received()
{
    QByteArray data = socket->readAll();
    cout << "Received!: " << data.toStdString() << endl;
}

void MainWindow::Online_Button_Action()
{
    //std::cout << "Online Button Pressed" << std::endl;
    Stacked_Widget->setCurrentWidget(Lobby_List_Page);
}
void MainWindow::Offline_Button_Action()
{   
    Stacked_Widget->setCurrentWidget(Game_Page);

    GameWidget* game = new GameWidget(GameType::CHESS_2, Color::WHITE);
    Game_Page_Layout->addWidget(game);

    
    //std::cout << "Offline Button Pressed" << std::endl;
}
void MainWindow::Create_Lobby_Button_Action()
{
    std::cout << "Create Lobby Button Pressed" << std::endl;
}
void MainWindow::Join_Lobby_Button_Action()
{
    std::cout << "Join Lobby Button Pressed" << std::endl;
}
void MainWindow::Update_Lobby_List_Button_Action()
{
    std::cout << "Update Lobby List Button Pressed" << std::endl;
}


void MainWindow::SocketTest()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.1.14", 4444);
    if (socket->waitForConnected(5000))
    {
        cout << "Connected!";
    }


}
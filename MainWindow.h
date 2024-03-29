#include "QtDesigner.h"
#include "GameWidget.cpp"
#include <QMainWindow>



class MainWindow : public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow();

private slots:
    void Online_Button_Action();
    void Offline_Button_Action();
    void Create_Lobby_Button_Action();
    void Join_Lobby_Button_Action();
    void Update_Lobby_List_Button_Action();


}
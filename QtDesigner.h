/********************************************************************************
** Form generated from reading UI file 'PyQtDesigner.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TEST_H
#define TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTabWidget *Chat_Tab_Widget;
    QWidget *Global_Chat_Tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *Global_Chat_Tab_Layout;
    QTextEdit *Global_Chat_Text_Edit;
    QWidget *Lobby_Chat_Tab;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *Lobby_Chat_Tab_Layout;
    QTextEdit *Lobby_Chat_Text_Edit;
    QLineEdit *Message_Input_Box;
    QStackedWidget *Stacked_Widget;
    QWidget *Connection_Page;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *Connection_Page_Layout;
    QSpacerItem *verticalSpacer;
    QPushButton *Offline_Button;
    QLineEdit *IP_Input_Box;
    QComboBox *IP_ComboBox;
    QComboBox *Name_ComboBox;
    QLineEdit *Name_Input_Box;
    QPushButton *Online_Button;
    QSpacerItem *verticalSpacer_2;
    QWidget *Lobby_List_Page;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *Lobby_List_Page_Layout;
    QTreeWidget *Lobby_List_Tree_Widget;
    QHBoxLayout *Lobby_List_Page_Buttons_Layout;
    QPushButton *Create_Lobby_Button;
    QPushButton *Join_Lobby_Button;
    QPushButton *Update_Lobby_List_Button;
    QWidget *Lobby_Creation_Page;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *Lobby_Creation_Layout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *Checkers_2_Button;
    QPushButton *Chess_4_Button;
    QPushButton *Chess_2_Button;
    QPushButton *Exit_Lobby_Creation_Button;
    QSpacerItem *verticalSpacer_4;
    QWidget *Lobby_Info_Page;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *Lobby_Info_Page_Layout;
    QHBoxLayout *Lobby_Info_Labels_Layout;
    QLabel *Lobby_ID_Label;
    QLabel *Lobby_Type_Label;
    QLabel *Lobby_Players_Label;
    QTreeWidget *Lobby_Info_Tree_Widget;
    QHBoxLayout *Lobby_Info_Buttons_Layput;
    QPushButton *Leave_Lobby_Button;
    QPushButton *Start_Lobby_Button;
    QPushButton *Kick_Player_Button;
    QWidget *Game_Page;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *Game_Page_Layout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(867, 607);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-10, 0, 881, 611));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        Chat_Tab_Widget = new QTabWidget(gridLayoutWidget);
        Chat_Tab_Widget->setObjectName(QString::fromUtf8("Chat_Tab_Widget"));
        Global_Chat_Tab = new QWidget();
        Global_Chat_Tab->setObjectName(QString::fromUtf8("Global_Chat_Tab"));
        verticalLayoutWidget = new QWidget(Global_Chat_Tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 211, 541));
        Global_Chat_Tab_Layout = new QVBoxLayout(verticalLayoutWidget);
        Global_Chat_Tab_Layout->setObjectName(QString::fromUtf8("Global_Chat_Tab_Layout"));
        Global_Chat_Tab_Layout->setContentsMargins(0, 0, 0, 0);
        Global_Chat_Text_Edit = new QTextEdit(verticalLayoutWidget);
        Global_Chat_Text_Edit->setObjectName(QString::fromUtf8("Global_Chat_Text_Edit"));
        Global_Chat_Text_Edit->setReadOnly(true);

        Global_Chat_Tab_Layout->addWidget(Global_Chat_Text_Edit);

        Chat_Tab_Widget->addTab(Global_Chat_Tab, QString());
        Lobby_Chat_Tab = new QWidget();
        Lobby_Chat_Tab->setObjectName(QString::fromUtf8("Lobby_Chat_Tab"));
        verticalLayoutWidget_2 = new QWidget(Lobby_Chat_Tab);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 211, 541));
        Lobby_Chat_Tab_Layout = new QVBoxLayout(verticalLayoutWidget_2);
        Lobby_Chat_Tab_Layout->setObjectName(QString::fromUtf8("Lobby_Chat_Tab_Layout"));
        Lobby_Chat_Tab_Layout->setContentsMargins(0, 0, 0, 0);
        Lobby_Chat_Text_Edit = new QTextEdit(verticalLayoutWidget_2);
        Lobby_Chat_Text_Edit->setObjectName(QString::fromUtf8("Lobby_Chat_Text_Edit"));
        Lobby_Chat_Text_Edit->setReadOnly(true);

        Lobby_Chat_Tab_Layout->addWidget(Lobby_Chat_Text_Edit);

        Chat_Tab_Widget->addTab(Lobby_Chat_Tab, QString());

        gridLayout->addWidget(Chat_Tab_Widget, 0, 1, 1, 1);

        Message_Input_Box = new QLineEdit(gridLayoutWidget);
        Message_Input_Box->setObjectName(QString::fromUtf8("Message_Input_Box"));

        gridLayout->addWidget(Message_Input_Box, 1, 1, 1, 1);

        Stacked_Widget = new QStackedWidget(gridLayoutWidget);
        Stacked_Widget->setObjectName(QString::fromUtf8("Stacked_Widget"));
        Connection_Page = new QWidget();
        Connection_Page->setObjectName(QString::fromUtf8("Connection_Page"));
        verticalLayoutWidget_4 = new QWidget(Connection_Page);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(30, 10, 501, 551));
        Connection_Page_Layout = new QVBoxLayout(verticalLayoutWidget_4);
        Connection_Page_Layout->setObjectName(QString::fromUtf8("Connection_Page_Layout"));
        Connection_Page_Layout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Connection_Page_Layout->addItem(verticalSpacer);

        Offline_Button = new QPushButton(verticalLayoutWidget_4);
        Offline_Button->setObjectName(QString::fromUtf8("Offline_Button"));

        Connection_Page_Layout->addWidget(Offline_Button);

        IP_Input_Box = new QLineEdit(verticalLayoutWidget_4);
        IP_Input_Box->setObjectName(QString::fromUtf8("IP_Input_Box"));

        Connection_Page_Layout->addWidget(IP_Input_Box);

        IP_ComboBox = new QComboBox(verticalLayoutWidget_4);
        IP_ComboBox->setObjectName(QString::fromUtf8("IP_ComboBox"));
        IP_ComboBox->setEditable(true);
        IP_ComboBox->setMaxVisibleItems(5);

        Connection_Page_Layout->addWidget(IP_ComboBox);

        Name_ComboBox = new QComboBox(verticalLayoutWidget_4);
        Name_ComboBox->setObjectName(QString::fromUtf8("Name_ComboBox"));
        Name_ComboBox->setAutoFillBackground(false);
        Name_ComboBox->setEditable(true);
        Name_ComboBox->setMaxVisibleItems(5);

        Connection_Page_Layout->addWidget(Name_ComboBox);

        Name_Input_Box = new QLineEdit(verticalLayoutWidget_4);
        Name_Input_Box->setObjectName(QString::fromUtf8("Name_Input_Box"));

        Connection_Page_Layout->addWidget(Name_Input_Box);

        Online_Button = new QPushButton(verticalLayoutWidget_4);
        Online_Button->setObjectName(QString::fromUtf8("Online_Button"));

        Connection_Page_Layout->addWidget(Online_Button);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Connection_Page_Layout->addItem(verticalSpacer_2);

        Stacked_Widget->addWidget(Connection_Page);
        Lobby_List_Page = new QWidget();
        Lobby_List_Page->setObjectName(QString::fromUtf8("Lobby_List_Page"));
        verticalLayoutWidget_3 = new QWidget(Lobby_List_Page);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 10, 561, 581));
        Lobby_List_Page_Layout = new QVBoxLayout(verticalLayoutWidget_3);
        Lobby_List_Page_Layout->setObjectName(QString::fromUtf8("Lobby_List_Page_Layout"));
        Lobby_List_Page_Layout->setContentsMargins(0, 0, 0, 0);
        Lobby_List_Tree_Widget = new QTreeWidget(verticalLayoutWidget_3);
        Lobby_List_Tree_Widget->setObjectName(QString::fromUtf8("Lobby_List_Tree_Widget"));

        Lobby_List_Page_Layout->addWidget(Lobby_List_Tree_Widget);

        Lobby_List_Page_Buttons_Layout = new QHBoxLayout();
        Lobby_List_Page_Buttons_Layout->setObjectName(QString::fromUtf8("Lobby_List_Page_Buttons_Layout"));
        Create_Lobby_Button = new QPushButton(verticalLayoutWidget_3);
        Create_Lobby_Button->setObjectName(QString::fromUtf8("Create_Lobby_Button"));

        Lobby_List_Page_Buttons_Layout->addWidget(Create_Lobby_Button);

        Join_Lobby_Button = new QPushButton(verticalLayoutWidget_3);
        Join_Lobby_Button->setObjectName(QString::fromUtf8("Join_Lobby_Button"));

        Lobby_List_Page_Buttons_Layout->addWidget(Join_Lobby_Button);

        Update_Lobby_List_Button = new QPushButton(verticalLayoutWidget_3);
        Update_Lobby_List_Button->setObjectName(QString::fromUtf8("Update_Lobby_List_Button"));

        Lobby_List_Page_Buttons_Layout->addWidget(Update_Lobby_List_Button);


        Lobby_List_Page_Layout->addLayout(Lobby_List_Page_Buttons_Layout);

        Stacked_Widget->addWidget(Lobby_List_Page);
        Lobby_Creation_Page = new QWidget();
        Lobby_Creation_Page->setObjectName(QString::fromUtf8("Lobby_Creation_Page"));
        verticalLayoutWidget_7 = new QWidget(Lobby_Creation_Page);
        verticalLayoutWidget_7->setObjectName(QString::fromUtf8("verticalLayoutWidget_7"));
        verticalLayoutWidget_7->setGeometry(QRect(60, 49, 521, 531));
        Lobby_Creation_Layout = new QVBoxLayout(verticalLayoutWidget_7);
        Lobby_Creation_Layout->setObjectName(QString::fromUtf8("Lobby_Creation_Layout"));
        Lobby_Creation_Layout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Lobby_Creation_Layout->addItem(verticalSpacer_3);

        Checkers_2_Button = new QPushButton(verticalLayoutWidget_7);
        Checkers_2_Button->setObjectName(QString::fromUtf8("Checkers_2_Button"));

        Lobby_Creation_Layout->addWidget(Checkers_2_Button);

        Chess_4_Button = new QPushButton(verticalLayoutWidget_7);
        Chess_4_Button->setObjectName(QString::fromUtf8("Chess_4_Button"));

        Lobby_Creation_Layout->addWidget(Chess_4_Button);

        Chess_2_Button = new QPushButton(verticalLayoutWidget_7);
        Chess_2_Button->setObjectName(QString::fromUtf8("Chess_2_Button"));

        Lobby_Creation_Layout->addWidget(Chess_2_Button);

        Exit_Lobby_Creation_Button = new QPushButton(verticalLayoutWidget_7);
        Exit_Lobby_Creation_Button->setObjectName(QString::fromUtf8("Exit_Lobby_Creation_Button"));

        Lobby_Creation_Layout->addWidget(Exit_Lobby_Creation_Button);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Lobby_Creation_Layout->addItem(verticalSpacer_4);

        Stacked_Widget->addWidget(Lobby_Creation_Page);
        Lobby_Info_Page = new QWidget();
        Lobby_Info_Page->setObjectName(QString::fromUtf8("Lobby_Info_Page"));
        verticalLayoutWidget_5 = new QWidget(Lobby_Info_Page);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(10, 10, 611, 581));
        Lobby_Info_Page_Layout = new QVBoxLayout(verticalLayoutWidget_5);
        Lobby_Info_Page_Layout->setObjectName(QString::fromUtf8("Lobby_Info_Page_Layout"));
        Lobby_Info_Page_Layout->setContentsMargins(0, 0, 0, 0);
        Lobby_Info_Labels_Layout = new QHBoxLayout();
        Lobby_Info_Labels_Layout->setObjectName(QString::fromUtf8("Lobby_Info_Labels_Layout"));
        Lobby_ID_Label = new QLabel(verticalLayoutWidget_5);
        Lobby_ID_Label->setObjectName(QString::fromUtf8("Lobby_ID_Label"));

        Lobby_Info_Labels_Layout->addWidget(Lobby_ID_Label);

        Lobby_Type_Label = new QLabel(verticalLayoutWidget_5);
        Lobby_Type_Label->setObjectName(QString::fromUtf8("Lobby_Type_Label"));

        Lobby_Info_Labels_Layout->addWidget(Lobby_Type_Label);

        Lobby_Players_Label = new QLabel(verticalLayoutWidget_5);
        Lobby_Players_Label->setObjectName(QString::fromUtf8("Lobby_Players_Label"));

        Lobby_Info_Labels_Layout->addWidget(Lobby_Players_Label);


        Lobby_Info_Page_Layout->addLayout(Lobby_Info_Labels_Layout);

        Lobby_Info_Tree_Widget = new QTreeWidget(verticalLayoutWidget_5);
        Lobby_Info_Tree_Widget->setObjectName(QString::fromUtf8("Lobby_Info_Tree_Widget"));

        Lobby_Info_Page_Layout->addWidget(Lobby_Info_Tree_Widget);

        Lobby_Info_Buttons_Layput = new QHBoxLayout();
        Lobby_Info_Buttons_Layput->setObjectName(QString::fromUtf8("Lobby_Info_Buttons_Layput"));
        Leave_Lobby_Button = new QPushButton(verticalLayoutWidget_5);
        Leave_Lobby_Button->setObjectName(QString::fromUtf8("Leave_Lobby_Button"));

        Lobby_Info_Buttons_Layput->addWidget(Leave_Lobby_Button);

        Start_Lobby_Button = new QPushButton(verticalLayoutWidget_5);
        Start_Lobby_Button->setObjectName(QString::fromUtf8("Start_Lobby_Button"));

        Lobby_Info_Buttons_Layput->addWidget(Start_Lobby_Button);

        Kick_Player_Button = new QPushButton(verticalLayoutWidget_5);
        Kick_Player_Button->setObjectName(QString::fromUtf8("Kick_Player_Button"));

        Lobby_Info_Buttons_Layput->addWidget(Kick_Player_Button);


        Lobby_Info_Page_Layout->addLayout(Lobby_Info_Buttons_Layput);

        Stacked_Widget->addWidget(Lobby_Info_Page);
        Game_Page = new QWidget();
        Game_Page->setObjectName(QString::fromUtf8("Game_Page"));
        verticalLayoutWidget_6 = new QWidget(Game_Page);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(50, 0, 591, 571));
        Game_Page_Layout = new QVBoxLayout(verticalLayoutWidget_6);
        Game_Page_Layout->setObjectName(QString::fromUtf8("Game_Page_Layout"));
        Game_Page_Layout->setContentsMargins(0, 0, 0, 0);
        Stacked_Widget->addWidget(Game_Page);

        gridLayout->addWidget(Stacked_Widget, 0, 0, 2, 1);

        gridLayout->setColumnStretch(0, 8);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        Chat_Tab_Widget->setCurrentIndex(0);
        Stacked_Widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Game Hub", nullptr));
        Chat_Tab_Widget->setTabText(Chat_Tab_Widget->indexOf(Global_Chat_Tab), QCoreApplication::translate("MainWindow", "Global Chat", nullptr));
        Chat_Tab_Widget->setTabText(Chat_Tab_Widget->indexOf(Lobby_Chat_Tab), QCoreApplication::translate("MainWindow", "Lobby Chat", nullptr));
        Message_Input_Box->setInputMask(QString());
        Message_Input_Box->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter message...", nullptr));
        Offline_Button->setText(QCoreApplication::translate("MainWindow", "Offline", nullptr));
        IP_Input_Box->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter server ip...", nullptr));
        IP_ComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter server ip...", nullptr));
        Name_ComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your name...", nullptr));
        Name_Input_Box->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your name...", nullptr));
        Online_Button->setText(QCoreApplication::translate("MainWindow", "Online", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = Lobby_List_Tree_Widget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("MainWindow", "Live", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Game Type", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Players", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Lobby ID", nullptr));
        Create_Lobby_Button->setText(QCoreApplication::translate("MainWindow", "Create Lobby", nullptr));
        Join_Lobby_Button->setText(QCoreApplication::translate("MainWindow", "Join Lobby", nullptr));
        Update_Lobby_List_Button->setText(QCoreApplication::translate("MainWindow", "Update Lobby List", nullptr));
        Checkers_2_Button->setText(QCoreApplication::translate("MainWindow", "Checkers (2 Players)", nullptr));
        Chess_4_Button->setText(QCoreApplication::translate("MainWindow", "Chess (4 Players)", nullptr));
        Chess_2_Button->setText(QCoreApplication::translate("MainWindow", "Chess (2 Players)", nullptr));
        Exit_Lobby_Creation_Button->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        Lobby_ID_Label->setText(QCoreApplication::translate("MainWindow", "Lobby ID:", nullptr));
        Lobby_Type_Label->setText(QCoreApplication::translate("MainWindow", "Lobby Type:", nullptr));
        Lobby_Players_Label->setText(QCoreApplication::translate("MainWindow", "Players:", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = Lobby_Info_Tree_Widget->headerItem();
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("MainWindow", "Color", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "Name", nullptr));
        Leave_Lobby_Button->setText(QCoreApplication::translate("MainWindow", "Leave Lobby", nullptr));
        Start_Lobby_Button->setText(QCoreApplication::translate("MainWindow", "Start Lobby", nullptr));
        Kick_Player_Button->setText(QCoreApplication::translate("MainWindow", "Kick Player", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TEST_H

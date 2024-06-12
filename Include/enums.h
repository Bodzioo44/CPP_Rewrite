#ifndef ENUMS_H
#define ENUMS_H

#include <map>
#include <QtCore/QString>
using std::map;

namespace Enums
{
    enum class Color
    {
        WHITE,
        BLACK
    };

    enum class GameType
    {
        CHECKERS_2,
        CHESS_2,
        CHESS_4
    };

    enum class SquareState 
    {
        INVALID,
        EMPTY,
        TAKEN_BY_ENEMY,
        TAKEN_BY_FRIENDLY
    };

    const map<GameType, int> GameType_vals = 
    {
      {GameType::CHECKERS_2, 2},
      {GameType::CHESS_2, 2},
      {GameType::CHESS_4, 4}  
    };
}

namespace API
{
    //Server to Client Join_Lobby and Create_Lobby is the same.
    const QString JOIN_LOBBY = "Join_Lobby";
    const QString CREATE_LOBBY = "Create_Lobby";
    const QString LEAVE_LOBBY = "Leave_Lobby";
    const QString REQUEST_LOBBY_LIST = "Request_Lobby_List";
    const QString UPDATE_LOBBY_LIST = "Update_Lobby_List";
    const QString KICK_PLAYER = "Kick_Player";  
    const QString START_LOBBY = "Start_Lobby";
    const QString MESSAGE = "Message";
    const QString LOBBY_MESSAGE = "Lobby_Message";
    const QString GLOBAL_MESSAGE = "Global_Message";
    const QString GAME_UPDATE = "Game_Update";
    const QString ASSIGN_NAME = "Assign_Name";
    const QString DISCONNECT = "Disconnect";
    const QString UPDATE_LOBBY = "Update_Lobby";
    const QString GAME_HISTORY = "Game_History";
    const QString RECONNECT = "Reconnect";
}



#endif
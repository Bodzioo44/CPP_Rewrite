#ifndef ENUMS_H
#define ENUMS_H

#include <map>
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


#endif
#ifndef GET_API_JSON_H
#define GET_API_JSON_H

#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QFile>

#include <iostream>
using namespace std;



QJsonObject Get_Api_Json_Obj()
{
    QFile API_Calls("Include/API_Calls.json");
    API_Calls.open(QIODevice::ReadOnly | QIODevice::Text);
    QString raw_api_calls;
    raw_api_calls = API_Calls.readAll();
    API_Calls.close();
    QJsonDocument Json_api_calls_doc = QJsonDocument::fromJson(raw_api_calls.toUtf8());
    QJsonObject json_api_calls = Json_api_calls_doc.object();
    return json_api_calls;

    // for (auto key : json_api_calls.keys())
    // {
    //     QJsonValue val = json_api_calls[key];
    //     if (key == "Game_Update")
    //     {
    //         cout << val["type"].toString().toStdString() << endl;
    //     }
    // }

}




#endif
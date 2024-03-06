#ifndef LOADJSON_H
#define LOADJSON_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <QString>
#include <QDebug>

using json = nlohmann::json;

class LoadJson
{
public:
    LoadJson();

    json jsonData;
    std::vector<std::string> listKeys;
    std::vector<std::string> searchRelevant(std::string keyWord);

private:
    std::string toLower(std::string s);
};

#endif // LOADJSON_H

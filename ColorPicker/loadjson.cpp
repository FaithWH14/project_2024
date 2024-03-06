#include "loadjson.h"

LoadJson::LoadJson() {
    std::ifstream file("C:\\Users\\faithwh14\\Desktop\\QT projects\\ColorPicker\\popular_colors.json");
    if (!file) {
        qDebug() << "Failed to open file";
        return;
    }

    file >> jsonData;

    for (auto it=jsonData.begin(); it!=jsonData.end(); ++it){
        listKeys.push_back(it.key());
    }

    return;
}

std::vector<std::string> LoadJson::searchRelevant(std::string keyWord){
    std::vector<std::string> result;
    std::string test = "Blue";
    std::copy_if(listKeys.begin(), listKeys.end(), std::back_inserter(result), [&keyWord](const std::string& s){
        std::string temp;
        for (char gg: s){
            temp += std::tolower(gg);
        }
        return temp.find(keyWord) != std::string::npos;
    });

    return result;
}

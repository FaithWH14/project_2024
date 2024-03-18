#ifndef BUSETA_H
#define BUSETA_H

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <QString>

using json = nlohmann::json;

class BusETA
{
public:
    BusETA();
    std::string result;
    std::string etaNextBus;
    std::string etaNextBus2;
    std::string etaNextBus3;
    // std::string estimatedArrival;

    void getData(std::string busServiceNo, std::string busStopCode);

private:
    CURL *curl;
    std::string apiKey ="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";;
    std::string busStopCode = "67191";
    std::string apiUrl = "http://datamall2.mytransport.sg/ltaodataservice/BusArrivalv2?BusStopCode=";
    std::string buffer;

    json targetBusInfo;
    void getBusInfo(std::string bus_key);
};

#endif // BUSETA_H

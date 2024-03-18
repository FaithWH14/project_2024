#ifndef BUSINFO_H
#define BUSINFO_H

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <QString>

class BusInfo
{
public:
    BusInfo();
    std::string result;
    void getData();

private:
    CURL *curl;
    std::string apiKey ="WDprtCVZRTudVLQZ+IpMzg==";;
    std::string busStopCode = "67191";
    std::string apiUrl = "http://datamall2.mytransport.sg/ltaodataservice/BusArrivalv2?BusStopCode=" + busStopCode;
    std::string buffer;
};

#endif // BUSINFO_H

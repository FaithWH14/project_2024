#include "businfo.h"
#include <QDebug>

using json = nlohmann::json;

// size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
//     size_t totalSize = size * nmemb;
//     buffer->append(static_cast<char*>(contents), totalSize);

//     return totalSize;
// }

BusInfo::BusInfo() {
}

void BusInfo::getData() {
    qDebug() << "atention" << apiUrl;
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "SOMETHING IS WRONG" << std::endl;
        result = "something is wrong";
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("AccountKey: " + apiKey).c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "FAILED AT: " << curl_easy_strerror(res) << std::endl;
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        result = "something is wrong";
        return;
    }

    json data = json::parse(buffer);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    json BusInfo = data["Services"];
    json targetBusInfo;

    for (const auto& bus: BusInfo) {
        if (bus["ServiceNo"] == "102") {
            targetBusInfo = bus;
            break;
        }
    }

    if (targetBusInfo.empty()) {
        result = "Bus 80 not in services";
        return;
    }
    // } else {
    //     std::cout << "target bus info is: " << targetBusInfo << std::endl;
    // }

    result = targetBusInfo.dump();
}

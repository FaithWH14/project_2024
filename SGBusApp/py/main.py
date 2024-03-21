from bs4 import BeautifulSoup
import requests
import re
import pandas as pd
from typing import List


def get_bus_info(bus_route: int, firstOrSecond: int) -> List:
    url = ("https://www.sbstransit.com.sg/Service/BusService?ServiceNo"
        f"={bus_route}&ServiceType=Basic&Dir={firstOrSecond}")
    response = requests.get(url)

    if response.status_code != 200:
        raise Exception(f"Bus Service No {bus_route} SOMETHING IS WRONG")

    soup = BeautifulSoup(response.content, "html.parser")
    interest = []
    for td_value in soup.find_all("td"):
        # strip called as there are many blank space
        interest.append(td_value.text.strip())

    pattern = r"\b\d{5}\b"
    busStopCode_list = list(filter(lambda x: re.match(pattern, x), interest))

    busInfo_list = []

    if not busStopCode_list:
        raise Exception(f"Bus Service No {bus_route}, No bus stop code is generated!")
    for busStopCode in busStopCode_list:
        busIdx = interest.index(busStopCode)
        busStationName = interest[busIdx + 1]
        busStationName = busStationName.split("\r")[0]

        distance = interest[busIdx + 2]
        busInfo_list.append(
            (bus_route, firstOrSecond, busStopCode, busStationName, distance))

    return busInfo_list

def main():

    bus_routes = ["80", "10", "147", "190", "61", "30", "85", "167", "2", "100",
                "171", "195", "36", "97", "76", "502", "154", "143", "198",
                "123", "222", "147e", "97e", "518", "858", "969", "28", "26",
                "89", "53", "118"]
    # bus_routes = ["80"]

    allBusInfo_list = []
    for bus_route in bus_routes:
        for firstOrSecond in [1, 2]:
            try:
                busInfo_list = get_bus_info(bus_route, firstOrSecond)
            except Exception as err:
                print(err)
                break
            allBusInfo_list += busInfo_list
            print(f"Bus Route {bus_route} with {firstOrSecond} way is done")

    columns_name = ["BusRoute", "FirstOrSecond", "BusStopCode", "BusStationName",
                    "Distance"]
    df = pd.DataFrame( allBusInfo_list, columns=columns_name)
    print("dataframe is: \n", df)

    tmp_work_dir = r"C:/Users/faithwh14/Desktop/project_2024/MARCH/bs4_bus"
    df.to_csv(rf"{tmp_work_dir}/bus_info.csv")

if __name__ == "__main__":
    main()

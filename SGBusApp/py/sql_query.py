import sqlite3
from typing import List

def get_bus_stations() -> List:
    conn = sqlite3.connect("bus_info.db")

    cursor = conn.cursor()

    cursor.execute("SELECT DISTINCT(busstopcode), busstationname FROM bus_info")
    # cursor.execute("SELECT DISTINCT(busstopcode) FROM bus_info")
    conn.commit()

    rows = cursor.fetchall()

    busStations = []
    for row in rows:
        row = (str(row[0]), row[1])
        busStation = " - ".join(row)

        print(busStation)
        busStations.append(busStation)
        # busStations.append(str(*row))

    # print(busStations)
    print("The total numbers of bus station is: ", len(busStations))
    return busStations

if __name__ == "__main__":
    get_bus_stations()
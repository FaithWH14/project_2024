import pandas as pd
import sqlite3
import psycopg2
from typing import Literal

csv_file = "bus_info.csv"
db_file = "bus_info.db"

table_name = "bus_info"

def convertToDB(options: Literal["sqlite", "postgresql"]):
    df = pd.read_csv(csv_file)

    if options == "sqlite":
        conn = sqlite3.connect(db_file)

        df.to_sql(table_name, conn, if_exists="replace", index=False)
        conn.commit()
        conn.close()

    elif options == "postgresql":
        # PostgreSQL connection parameters
        pg_host = 'localhost'
        pg_port = '5432'
        pg_database = 'postgres'
        pg_user = 'postgres'
        pg_password = 'XXXX'

        table_name = "bus_info"

        conn = psycopg2.connect(
            host=pg_host, port=pg_port, database=pg_database,
            user=pg_user, password=pg_password)
        cur = conn.cursor()

        # Create a table in PostgreSQL from the DataFrame
        df_columns = list(df.columns)
        df_columns[0] = "index"
        db_columns = ", ".join([f"{column} TEXT" for column in df_columns])
        print("attention", db_columns)
        cur.execute(f"CREATE TABLE IF NOT EXISTS {table_name} ({db_columns});")

        # Insert DataFrame records into the PostgreSQL table
        for _, row in df.iterrows():
            cur.execute(f"INSERT INTO {table_name} VALUES ({','.join([f'%({col})s' for col in df.columns])});", row)

        # Commit changes and close cursor
        conn.commit()
        cur.close()
    else:
        raise Exception("Options should be only sqlite or postgresql")

    print(f"{options} Database {db_file} created successfully")

if __name__ == "__main__":
    convertToDB("postgresql")

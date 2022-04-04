/*
   Copyright (C) 2022 Fab by Nerdiy.de

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
    @file Json_data.h

    Class for reading json data object from provided URL.
*/
#pragma once
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#define MAX_COLUMNS   5
#define MAX_ROWS  10

/**
    Class for reading json data object from provided URL.
*/
class Json_data
{
  protected:

    /* Handles json data fetch and deserialisation of the json data. */
    bool GetJsonObject(DynamicJsonDocument &doc)
    {
      WiFiClient client;
      HTTPClient http;

      client.stop();
      http.begin(client, JSON_DATA_URL, JSON_DATA_PORT, JSON_DATA_PATH);

      int httpCode = http.GET();

      if (httpCode != HTTP_CODE_OK)
      {
        Serial.printf("Json data fetch failed, error: %s", http.errorToString(httpCode).c_str());
        client.stop();
        http.end();
        return false;
      } else
      {
        DeserializationError error = deserializeJson(doc, http.getStream());

        if (error)
        {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          return false;
        } else
        {
          return true;
        }
      }
    }

    /* Fill from the json data into the internal data. */
    bool Fill(const JsonObject &root)
    {

      JsonArray rows_json = root["Columns"];
      serializeJsonPretty(rows_json, Serial);

      for (int column_id = 0; column_id < MAX_COLUMNS; column_id++)
      {
        if (column_id < rows_json.size())
        {
          for (int row_id = 0; row_id < MAX_ROWS; row_id++)
          {
            if (row_id < rows_json[column_id]["row_names"].size())
            {
              row_names[column_id][row_id] = rows_json[column_id]["row_names"][row_id].as<char *>();
            }
            if (row_id < rows_json[column_id]["values"].size())
            {
              row_values[column_id][row_id] = rows_json[column_id]["values"][row_id].as<char *>();
            }
          }
        }
      }

      return true;
    }


  public:
    String row_names[MAX_COLUMNS][MAX_ROWS];          //!< description of the hourly forecast
    String row_values[MAX_COLUMNS][MAX_ROWS];          //!< description of the hourly forecast

    /* Start the request and the filling. */
    bool Get()
    {
      DynamicJsonDocument doc(35 * 1024);

      if (GetJsonObject(doc))
      {
        // serialize the array and send the result to Serial
        return Fill(doc.as<JsonObject>());
      }
      return false;
    }
};

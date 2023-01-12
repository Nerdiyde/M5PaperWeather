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
#include "base64.h"

#define MAX_COLUMNS   5
#define MAX_ROWS  10

/**
    Class for reading json data object from provided URL.
*/
class Json_data
{
  protected:

    /* Handles json data fetch and deserialisation of the json data. */
    bool GetJsonObject(DynamicJsonDocument &doc, int wifiRSSI, float batteryVolt, int batteryCapacity, int sht30Temperatur, int sht30Humidity)
    {
      HTTPClient http;

      //client.stop();

      String path = String(JSON_DATA_PATH)
                    + "?wifiRSSI=" + String(wifiRSSI)
                    + "&batteryVolt=" + String(batteryVolt)
                    + "&batteryCapacity=" + String(batteryCapacity)
                    + "&sht30Temperatur=" + String(sht30Temperatur)
                    + "&sht30Humidity=" + String(sht30Humidity);

Serial.print("Starting JSON data retrieval from: url:");
Serial.print(JSON_DATA_URL);
Serial.print(" port:");
Serial.print(JSON_DATA_PORT);
Serial.print(" path:");
Serial.println(path);

#if !defined(JSON_DATA_URL_USES_HTTPS)
      WiFiClient client;
      http.begin(client, JSON_DATA_URL, JSON_DATA_PORT, path);
#else
      WiFiClientSecure client;
      client.setInsecure();
      http.begin(client, JSON_DATA_URL, JSON_DATA_PORT, path, true);
#endif

#if defined(JSON_DATA_URL_USE_BASIC_AUTHENTICATION)
      String auth = String(JSON_DATA_USER) + ":" + String(JSON_DATA_PASSWORD);
      auth = base64::encode(auth);
      http.addHeader("Authorization", "Basic " + auth);
#endif

      int httpCode = http.GET();

      if (httpCode != HTTP_CODE_OK)
      {
        Serial.printf("Json data fetch failed, error: %s", http.errorToString(httpCode).c_str());
        Serial.println();
        client.stop();
        http.end();
        return false;
      } else
      {
        DeserializationError error = deserializeJson(doc, http.getStream());
        client.stop();
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
    bool Get(int wifiRSSI, float batteryVolt, int batteryCapacity, int sht30Temperatur, int sht30Humidity)
    {
      DynamicJsonDocument doc(35 * 1024);

      if (GetJsonObject(doc, wifiRSSI, batteryVolt, batteryCapacity, sht30Temperatur, sht30Humidity))
      {
        // serialize the array and send the result to Serial
        return Fill(doc.as<JsonObject>());
      }
      return false;
    }
};

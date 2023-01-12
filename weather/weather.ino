/*
   Copyright (C) 2021 SFini

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
    @file Weather.h

    Main file with setup() and loop()
*/

/*
   History:
   - 08.06.2022: 
     - Added support for device data transmission via GET parameter during the JSON data fetch
     - Added support to connect to (self signed) HTTPS endpoints to fetch JSON data
   - 14.06.2022:    
     - Added error message for in case JSON data can not be retrieved 
*/

#include <M5EPD.h>
#include "Config.h"
#include "ConfigOverride.h" // Remove this line
#include "Data.h"
#include "Display.h"
#include "Battery.h"
#include "EPD.h"
#include "EPDWifi.h"
#include "Moon.h"
#include "SHT30.h"
#include "Time.h"
#include "Utils.h"
#include "Weather.h"
#include "Json_data.h"

MyData         myData;            // The collection of the global data
WeatherDisplay myDisplay(myData); // The global display helper class

/* Start and M5Paper instance */
void setup()
{
  myData.LoadNVS();
  if (myData.nvsCounter == 1)
  {
    InitEPD(true);
    if (StartWiFi(myData.wifiRSSI))
    {
      GetBatteryValues(myData);
      GetSHT30Values(myData);
      GetMoonValues(myData);
      if (myData.weather.Get())
      {
        SetRTCDateTime(myData);
      }

#if defined(DISPLAY_JSON_DATA)
      boolean jsonData_fetch_success = myData.jsonData.Get(myData.wifiRSSI, myData.batteryVolt, myData.batteryCapacity, myData.sht30Temperatur, myData.sht30Humidity);
      if (jsonData_fetch_success)
      {
        Serial.println("Json data fetch successfull");
      } else
      {
        Serial.println("Json data fetch failed. :/");        
      }
#endif

      myData.Dump();
      myDisplay.Show(jsonData_fetch_success);
      StopWiFi();
    }
  } else
  {
    InitEPD(false);
    GetSHT30Values(myData);
    myDisplay.ShowM5PaperInfo();
    if (myData.nvsCounter >= WIFI_DATA_FETCH_DEVIDER)
    {
      myData.nvsCounter = 0;
    }
  }
  myData.nvsCounter++;
  myData.SaveNVS();
  ShutdownEPD(REFRESH_INTERVAL);
}

/* Main loop. Never reached because of shutdown */
void loop()
{
  /* M5 paper is not able to go to powerdown if the USB is still connected.
     This is some kind of workaround to simulate the powerdown and wakeup cycle while the USB is still connected.
  */

  if (millis() >= REFRESH_INTERVAL * 1000)
  {
    ESP.restart();
  }

}

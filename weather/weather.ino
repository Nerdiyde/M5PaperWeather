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

#include <M5EPD.h>
//#include "Config.h"
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
      if (myData.jsonData.Get())
      {
        Serial.println("Json data fetch successfull");
      }
#endif

      myData.Dump();
      myDisplay.Show();
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

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
  * @file Config.h
  * 
  * configuration information
  */
#pragma once

//Activate this if you want to update the loc
#define REFRESH_INTERVAL 600 // Display refresh interval in seconds. This is equivalent to the ESP32 sleep duration.

// This defines how often the data should be updated via Wifi. 
// If you set this to 2 data via wifi is fetched at every second wake up from deep sleep. E.g. you set REFRESH_INTERVAL to 600=10 minutes and WIFI_DATA_FETCH_DEVIDER to 2 the data is fetched every 20 minutes.
#define WIFI_DATA_FETCH_DEVIDER 2

#define VERSION          "Version 1.0"
#define HEADLINE_STRING        "ENTER_CITY_NAME_HERE"

// change to your location
#define LATITUDE         47.69732 
#define LONGITUDE         8.63493

#define OPENWEATHER_SRV  "api.openweathermap.org"
#define OPENWEATHER_PORT 80
#define OPENWEATHER_API  "ENTER_API_KEY_HERE"

#define WIFI_SSID        "ENTER_WIFI_SSID_HERE"
#define WIFI_PW          "ENTER_WIFI_PW_HERE"

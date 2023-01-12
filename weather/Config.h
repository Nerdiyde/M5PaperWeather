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

#define VERSION          "Version 1.0" // This is dispalyed in the top left corner
#define HEADLINE_STRING        "Headline text"  // This is dispalyed in the top center

// ========== Location data area  ========== 

#define LATITUDE         47.69732 
#define LONGITUDE         8.63493

// ========== Openweathermap area  ========== 

#define OPENWEATHER_SRV  "api.openweathermap.org"
#define OPENWEATHER_PORT 80
#define OPENWEATHER_API  "ENTER_API_KEY_HERE"

// ========== Wifi credentials area  ========== 

#define WIFI_SSID        "ENTER_WIFI_SSID_HERE"
#define WIFI_PW          "ENTER_WIFI_PW_HERE"

// ========== Sleep settings area  ========== 

#define REFRESH_INTERVAL 600 // Display refresh interval in seconds.

// This defines how often the data should be updated via Wifi in relation to the wakeup cycles.
// If you set this to 2 data via wifi is fetched at every second wake up from deep sleep. E.g. you set REFRESH_INTERVAL to 600=10 minutes and WIFI_DATA_FETCH_DEVIDER to 2 the data is fetched every 20 minutes.
#define WIFI_DATA_FETCH_DEVIDER 1

#define DISPLAY_ORIENTATION 2 // Set this to 0 if you want to have the USB port on the right side. Set it to 2 if you want to have the USB port on the right side.

// ========== Forecast display area  ========== 

// Define here which content should be displayed in the forecast display area. Select one of the available options
//#define DISPLAY_WEATHER_DETAILS_HOURLY // This displays a hourly forecast beginning from the current time
#define DISPLAY_WEATHER_DETAILS_DAILY // This displays a daily forecast beginngin from today

// ========== Bottom display area  ========== 

// Define here which content should be displayed in the bottom display area. Select one of the available options
//#define DISPLAY_WEATHER_DATA_GRAPH
#define DISPLAY_JSON_DATA

#define JSON_DATA_URL "ENTER_HOSTNAME_HERE" // Define the URL to your JSON data object here
#define JSON_DATA_PORT 1880 // Define the port to your JSON data object here
#define JSON_DATA_PATH "/json_test.json"

#define JSON_DATA_URL_USE_BASIC_AUTHENTICATION  // Define this if the basic authentication credentials shall be considered
#define JSON_DATA_USER "Username" // Username
#define JSON_DATA_PASSWORD "enterSecretPasswordHere" // Password

// ========== Sanity check: DO NOT CHANGE ANYTHING BELOW THIS LINE! ========== 

#if DISPLAY_ORIENTATION!=2 && DISPLAY_ORIENTATION!=0
#error The value for DISPLAY_ORIENTATION can only be 0 or 2. For other values the content can not be displayed.
#endif

#if (defined(DISPLAY_WEATHER_DATA_GRAPH) && defined(DISPLAY_JSON_DATA)) || (!defined(DISPLAY_WEATHER_DATA_GRAPH) && !defined(DISPLAY_JSON_DATA))
#error Please select either DISPLAY_WEATHER_DATA_GRAPH or DISPLAY_JSON_DATA.
#endif

#if (defined(DISPLAY_WEATHER_DETAILS_HOURLY) && defined(DISPLAY_WEATHER_DETAILS_DAILY)) || (!defined(DISPLAY_WEATHER_DETAILS_HOURLY) && !defined(DISPLAY_WEATHER_DETAILS_DAILY))
#error Please select either DISPLAY_WEATHER_DETAILS_HOURLY or DISPLAY_WEATHER_DETAILS_DAILY.
#endif

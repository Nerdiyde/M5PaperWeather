

## M5PaperWeather flavoured by Nerdiy.de

M5Paper weather display originally forked from https://github.com/Bastelschlumpf/M5PaperWeather
Including additional implementations from https://github.com/mzyy94/M5PaperWeather

   ![M5PaperWeather](images/M5PaperWeather.png "M5Paper")


### Description
  Arduino project to show internal environment data and weather information from 
  openweathermap.org on the E-ink display of the M5Paper.
  
  **Additional features added by Nerdiy.de:**
   - It is now possible to display information received via JSON in the bottom area instead of weather data graphs. See DISPLAY_JSON_DATA in config.h for more infos.
   - Added the functionality for daily forecasts from https://github.com/mzyy94/M5PaperWeather. You can now decide by using DISPLAY_WEATHER_DETAILS_HOURLY or DISPLAY_WEATHER_DETAILS_DAILY which forecast type you want.

  
  ### Installation:
  Detailed installation info at: 
  - Summary:
  -- Enter your wifi credentials, openweather map api key and position in config.h 

  * A header with version, city wifi strength and battery status
  * Sun section with sunrise and sunset 
  * Moon section with moonrise and moonset
  * Wind section with wind direction and wind speed
  * The internal SH30 sensor data (temperature and humidity) with the current date and time
  * A hourly forecast with hour, temperature and a weather icon.
  * Some detailt forecast graphs with temperature, rain, humidity and pressure

### Disclaimer
   I don't take any responsibility nor liability for using this software nor for the 
   installation or any tips, advice, videos, etc. given by any member of this site or any related site.

### License
This program is licensed under GPL-3.0

### Credits
* https://github.com/Bastelschlumpf/ : Thanks for providing this really cool impelmentation of a weather display.
* https://github.com/mzyy94/M5PaperWeather : Thanks for providing the functionality to display a daily forecast instead of an hourly one.
* https://www.arduino.cc : Thanks to the Arduino community with all its incredible possibilities and support.
* https://github.com/G6EJD/ESP32-Revised-Weather-Display-42-E-Paper : Special thanks for the drawing function of the moon and the wind section from David Bird.
     

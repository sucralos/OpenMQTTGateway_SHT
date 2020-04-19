/*  
  OpenMQTTGateway Addon  - ESP8266 or Arduino program for home automation 
   Act as a wifi or ethernet gateway between your 433mhz/infrared IR signal  and a MQTT broker 
   Send and receiving command by MQTT
 
    SHT3x reading Addon
  
    This file is part of OpenMQTTGateway.
    
    OpenMQTTGateway is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    OpenMQTTGateway is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "User_config.h"

#ifdef ZsensorSHT3x
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setupZsensorSHT3x()
{
  Log.notice(F("SHT3X Setup Begin: %H" CR), SHT3X_I2C_ADDR);
  Log.notice(F("SHT3X Init, result of .begin(): 0x %h" CR), sht31.begin(SHT3X_I2C_ADDR));
}

//Time used to wait for an interval before resending temp and hum
unsigned long timeSHT3x = 0;

// Library default is to read with high repeatability: ~ 15 ms
void MeasureTempAndHum(){
  if (millis() > (timeSHT3x + TimeBetweenReadingSHT3x)) 
  {//retrieving value of temperature and humidity of the box from DHT every xUL
    timeSHT3x = millis();
    static float persisted_sht_h;
    static float persisted_sht_t;
    float ShtHum = sht31.readHumidity();
    // Read temperature as Celsius (the default)
    float ShtTempC = sht31.readTemperature(); 
    // Check if any reads failed and exit early (to try again).
    if (isnan(ShtHum) || isnan(ShtTempC)) 
    {
      Log.error(F("Failed to read from SHT3x sensor!" CR));
    }
    else
    {
      Log.trace(F("Creating SHT Buffer" CR));
      StaticJsonBuffer<JSON_MSG_BUFFER> jsonBuffer;
      JsonObject &SHTdata = jsonBuffer.createObject();
      if(ShtHum != persisted_sht_h || sht3x_always)
      {
        SHTdata.set("tempc", (float)ShtTempC);
       }
       else
       {
        Log.trace(F("Same humidity, don't send it" CR));
       }
      if(ShtTempC != persisted_sht_t || sht3x_always)
      {
        SHTdata.set("hum", (float)ShtHum);
      }
      else
      {
        Log.trace(F("Same temperature, don't send it" CR));
      }
      if(SHTdata.size() > 0)
      {
          pub(SHTTOPIC, SHTdata);
      }
    }
    persisted_sht_h = ShtHum;
    persisted_sht_t = ShtTempC;
  }
}
#endif
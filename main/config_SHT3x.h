/*  
  OpenMQTTGateway  - ESP8266 or Arduino program for home automation 

   Act as a wifi or ethernet gateway between your 433mhz/infrared IR signal  and a MQTT broker 
   Send and receiving command by MQTT
 
   This files enables to set your parameters for the SHT3x sensor family
    
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
#ifndef config_SHT3x_h
#define config_SHT3x_h


#define SHTTOPIC "/SHTtoMQTT/sht"
#define sht3x_always true // if false when the current value for temp or hum is the same as previous one don't send it by MQTT
#define TimeBetweenReadingSHT3x 30000 // time between 2 DHT readings

extern void setupZsensorSHT3x();
extern void MeasureTempAndHum();

#define SHT3X_I2C_ADDR 0x44 // SHT3x I2C address, 0x44 or 0x45

#endif
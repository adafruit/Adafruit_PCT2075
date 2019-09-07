
/*!
 *  @file Adafruit_PCT2075.cpp
 *
 *  @mainpage Adafruit PCT2075 temperature sensor library
 *
 *  @section intro_sec Introduction
 *
 * 	I2C Driver for the NXP PCT2075 temperature sensor library
 * 
 * 	This is a library for the Adafruit PCT2075 breakout:
 * 	https://www.adafruit.com/product/4169
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section dependencies Dependencies
 *
 *  This library depends on the Adafruit BusIO library
 *
 *  @section author Author
 *
 *  Bryan Siepert for Adafruit Industries
 *
 * 	@section license License
 * 
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include "Arduino.h"
#include <Wire.h>

#include "Adafruit_PCT2075.h"

/*!
 *    @brief  Instantiates a new PCT2075 class
 */
Adafruit_PCT2075::Adafruit_PCT2075(void) {}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
boolean Adafruit_PCT2075::begin(uint8_t i2c_address, TwoWire *wire) {
  i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return _init();
}

boolean Adafruit_PCT2075::_init(void) {
  // Adafruit_BusIO_Register chip_id = 
  //   Adafruit_BusIO_Register(i2c_dev, PCT2075_DEVICE_ID, 2);

  // // make sure we're talking to the right chip
  // if (chip_id.read() != 0x0186) {
  //   return false;
  // }

  CONFIG = new Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_CONFIG, 1, MSBFIRST);

  return true;
}
/**************************************************************************/
/*!
    @brief Gets the current temperature measurement
    @return The current temperature in degrees C. Resolution is 0.125 C
*/

float Adafruit_PCT2075::getTemperature(void){
  Adafruit_BusIO_Register temperature =
      Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_TEMP, 2, MSBFIRST);
  int16_t raw_temp = temperature.read();
  return (float) ((raw_temp >>5)*0.125);
}

/**************************************************************************/
/*!
    @brief Gets the amount of time the sensor waits between measurements
    @return The amount of idle time in seconds
*/
uint8_t Adafruit_PCT2075::getIdleTime(void){
  Adafruit_BusIO_Register idle_time_reg =
  Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_TIDLE, 1, MSBFIRST);

  Adafruit_BusIO_RegisterBits idle_time =
  Adafruit_BusIO_RegisterBits(&idle_time_reg, 5, 0);
  return (uint8_t)idle_time.read();
}
/**************************************************************************/
/*!
    @brief Sets the amount of time the sensor waits between measurements
    @param  new_idle_time
            The new idle time in seconds. Must be >= 0.1, <= 3.2 and a multiple
            of 0.1 (100 ms)
*/
void Adafruit_PCT2075::setIdleTime(uint8_t new_idle_time){
  Adafruit_BusIO_Register idle_time_reg =
    Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_TIDLE, 1, MSBFIRST);
  
    Adafruit_BusIO_RegisterBits idle_time =
    Adafruit_BusIO_RegisterBits(&idle_time_reg, 5, 0);

    idle_time.write(new_idle_time);
}
/**************************************************************************/
/*!
    @brief Sets the polarity of the INT pin
    @param  active_high
            The polarity of the INT pin. If true the INT pin is Hi-Z on alert.
            If false, the INT pin is connected to ground on alert.
*/
void Adafruit_PCT2075::setActiveHigh(bool active_high) {
    Adafruit_BusIO_RegisterBits active_high_bit =
    Adafruit_BusIO_RegisterBits(CONFIG, 1, 2);
    active_high_bit.write(active_high);
}

/**************************************************************************/
/*!
    @brief Gets the temperature hysteresis value in degrees C
    @return The temperature hysteresis value in degrees C. Resolution is 0.5 C
*/
float Adafruit_PCT2075::getTemperatureHysteresis(void){
  Adafruit_BusIO_Register temp_hyst_register =
      Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_THYST, 2, MSBFIRST);
  int16_t raw_hyst = temp_hyst_register.read();

  return (float) ((raw_hyst >>7)*0.5);
}
/**************************************************************************/
/*!
    @brief Sets the temperature hysteresis value in degrees C
    @param  temp_hysteresis
            The new high temperature threshold in degrees C. Resolution is 0.5 C
*/
void Adafruit_PCT2075::setTemperatureHysteresis(float temp_hysteresis){
  Adafruit_BusIO_Register temp_hyst_register =
      Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_THYST, 2, MSBFIRST);
  int16_t new_raw_hyst = ((uint16_t)(temp_hysteresis * 2) <<7);
  temp_hyst_register.write(new_raw_hyst);
}
/**************************************************************************/
/*!
    @brief Gets the high temperature threshold in degrees C
    @return The current high temperature threshold in degrees C. Resolution is 0.5 C
*/
float Adafruit_PCT2075::getHighTemperatureThreshold(void){
  Adafruit_BusIO_Register high_temp_register =
      Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_TOS, 2, MSBFIRST);
  int16_t raw_temp = high_temp_register.read();

  return (float) ((raw_temp >>7)*0.5);
}
/**************************************************************************/
/*!
    @brief Sets the high temperature threshold in degrees C
    @param  new_temp_threshold
            The new high temperature threshold in degrees C. Resolution is 0.5 C
*/

void Adafruit_PCT2075::setHighTemperatureThreshold(float new_temp_threshold){
  Adafruit_BusIO_Register high_temp_register =
      Adafruit_BusIO_Register(i2c_dev, PCT2075_REGISTER_TOS, 2, MSBFIRST);
  int16_t new_raw_temp = ((uint16_t)(new_temp_threshold * 2) <<7);
  high_temp_register.write(new_raw_temp);
}

pct2075_mode_t Adafruit_PCT2075::getMode(void){
    Adafruit_BusIO_RegisterBits mode_bit =
      Adafruit_BusIO_RegisterBits(CONFIG, 1, 1);
    return (pct2075_mode_t)mode_bit.read();
}
void Adafruit_PCT2075::setMode(pct2075_mode_t mode){
    Adafruit_BusIO_RegisterBits mode_bit =
      Adafruit_BusIO_RegisterBits(CONFIG, 1, 1);
    mode_bit.write(mode);
}

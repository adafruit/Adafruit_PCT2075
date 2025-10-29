// SPDX-FileCopyrightText: 2019 Bryan Siepert for Adafruit Industries
//
// SPDX-License-Identifier: BSD

#include <Adafruit_PCT2075.h>

Adafruit_PCT2075 PCT2075;

uint8_t i2c_addr = PCT2075_I2CADDR_DEFAULT  // default address (see guide for others)

void setup() {
  PCT2075 = Adafruit_PCT2075();

  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }
  Serial.println("Adafruit PCT2075 Test");

  if (!PCT2075.begin(i2c_addr)) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  
  Serial.println("Found PCT2075 chip");

}

void loop() {
  Serial.print("Temperature: "); Serial.print(PCT2075.getTemperature());Serial.println(" C");
  delay(1000);
}

// SPDX-FileCopyrightText: 2019 Bryan Siepert for Adafruit Industries
//
// SPDX-License-Identifier: BSD

#include <Adafruit_PCT2075.h>

Adafruit_PCT2075 pct;
uint8_t i2c_addr = PCT2075_I2CADDR_DEFAULT;  // default address (see guide for others)

void setup() {
  // pct = Adafruit_PCT2075();

  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }
  Serial.println("Adafruit PCT2075 Test");

  if (!pct.begin(i2c_addr)) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  
  Serial.println("Found PCT2075 chip");
  pct.setIdleTime(1.0);
  pct.setActiveHigh(true); 
  
  pct.setHighTemperatureThreshold(32.5);
  Serial.print("High temperature threshold: ");Serial.print(pct.getHighTemperatureThreshold()); Serial.println("");
  
  pct.setTemperatureHysteresis(30.5);
  Serial.print("Temperature hysteresis: ");Serial.print(pct.getTemperatureHysteresis()); Serial.println("");
  
  pct.setMode(PCT2075_MODE_COMPARITOR);
  Serial.print("Alert mode set to: ");
  switch (pct.getMode()) {
    case PCT2075_MODE_INTERRUPT: Serial.println("Interrupt"); break;
    case PCT2075_MODE_COMPARITOR: Serial.println("Comparitor"); break;
  }

  pct.setFaultCount(PCT2075_FAULT_COUNT_4); // since the loop timing and idle delay are in sync, it will take 4 loops to fault
  Serial.print("Fault count set to: ");
  switch (pct.getFaultCount()) {
    case PCT2075_FAULT_COUNT_1: Serial.println("1"); break;
    case PCT2075_FAULT_COUNT_2: Serial.println("2"); break;
    case PCT2075_FAULT_COUNT_4: Serial.println("4"); break;
    case PCT2075_FAULT_COUNT_6: Serial.println("6"); break;
  }
  
}

void loop() {
  // checking every
  Serial.print("Temperature: "); Serial.print(pct.getTemperature());Serial.println(" C");
  delay(1000); // wait one second to match the idle time
}

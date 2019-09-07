#include <Adafruit_PCT2075.h>


Adafruit_PCT2075 pct;

void setup() {
  pct = Adafruit_PCT2075();

  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }
  Serial.println("Adafruit PCT2075 Test");

  if (!pct.begin(0x48)) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  
  Serial.println("Found PCT2075 chip");
  pct.setIdleTime(1); // 10 *100ms = 1 second
  pct.setActiveHigh(true); 
  
  pct.setHighTemperatureThreshold(32.5);
  Serial.print("High temperature threshold: ");Serial.print(pct.getHighTemperatureThreshold()); Serial.println("");
  
  pct.setTemperatureHysteresis(30.5);
  Serial.print("temperature hysteresis: ");Serial.print(pct.getTemperatureHysteresis()); Serial.println("");
  
  pct.setMode(PCT2075_MODE_COMPARITOR);
  Serial.print("Alert mode set to: ");
  switch (pct.getMode()) {
    case PCT2075_MODE_INTERRUPT: Serial.println("Interrupt"); break;
    case PCT2075_MODE_COMPARITOR: Serial.println("Comparitor"); break;
  }
  
}

void loop() {
  // checking every
  Serial.print("Temperature: "); Serial.print(pct.getTemperature());Serial.println(" C");
  delay(500);
}

#include <Adafruit_PCT2075.h>


Adafruit_PCT2075 PCT2075;

void setup() {
  PCT2075 = Adafruit_PCT2075();

  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }
  Serial.println("Adafruit PCT2075 Test");

  if (!PCT2075.begin(0x48)) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  
  Serial.println("Found PCT2075 chip");
  PCT2075.setIdleTime(10); // 10 *100ms = 1 second
  delay(100);
  Serial.print("Idle time between measurements: ");Serial.print(PCT2075.getIdleTime());Serial.println("");

}

void loop() {
  // checking every
  Serial.print("Temperature: "); Serial.print(PCT2075.getTemperature());Serial.println(" C");
  delay(500);
}

#include <LBLE.h>
#include "Arduino.h"
#include "EasyPeriphral.h"

const int sensor = 14;
const int usr_btn = 6;
const int SAMPLE_RATE = 500;
String data;
EasyPeriphral peri;

void setup() {  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  // Initialize BLE subsystem
  LBLE.begin();
  while (!LBLE.ready()) { delay(100); }
  String address = LBLE.getDeviceAddress().toString();
  Serial.println("BLE ready");
  Serial.print("Device Address = [");
  Serial.print(LBLE.getDeviceAddress());
  Serial.println("]");

  peri.setDeviceName("LBLE-HAHA");
  peri.begin();
  pinMode(sensor, INPUT);

}

void loop() { 
   delay(SAMPLE_RATE);
   int r = analogRead(sensor);
   Serial.println(r);
   Serial.print("conected=");
   Serial.println(peri.connected());
   peri.broadcast(r);
}

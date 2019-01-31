#include <LBLE.h>
#include <LBLEPeriphral.h>
#include "Arduino.h"

const int sensor = 14;
const int usr_btn = 6;
const int SAMPLE_RATE = 500;
String data;
char* devName = "LBLE-test";

char* serviceUUID = "00001802-0000-1000-8000-00805f9b34fb";
LBLEUuid uuid(serviceUUID);

LBLEService uartService(serviceUUID);
LBLECharacteristicString rxCharacteristic("00002a04-0000-1000-8000-00805f9b34fb", LBLE_READ | LBLE_WRITE);//Rx
LBLECharacteristicString txCharacteristic("00002a05-0000-1000-8000-00805f9b34fb", LBLE_READ | LBLE_WRITE);//Rx

void setup() {  

  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // Initialize BLE subsystem
  LBLE.begin();
  while (!LBLE.ready()) {
    delay(100);
  }

  String address = LBLE.getDeviceAddress().toString();

  Serial.println("BLE ready");
  Serial.print("Device Address = [");
  Serial.print(LBLE.getDeviceAddress());
  Serial.println("]");
  Serial.print("BLE Name = ");
  Serial.println(devName);
  
  LBLEAdvertisementData advertisement;
  advertisement.configAsConnectableDevice(devName, serviceUUID);

  
  LBLEPeripheral.setName(devName);

  uartService.addAttribute(txCharacteristic);
  uartService.addAttribute(rxCharacteristic);

  LBLEPeripheral.addService(uartService);
  

  LBLEPeripheral.advertise(advertisement);

  LBLEPeripheral.begin();
  
  pinMode(sensor, INPUT);

}

void loop() { 
  delay(SAMPLE_RATE);
  int r = analogRead(sensor);
  Serial.println(r);
 Serial.print("conected=");
 Serial.println(LBLEPeripheral.connected());
  if(LBLEPeripheral.connected())
  {

    txCharacteristic.setValue(String(r));
    LBLEPeripheral.notifyAll(txCharacteristic);
  
  }

  if(rxCharacteristic.isWritten()){
    data = rxCharacteristic.getValue();
    Serial.print("Rx=");
    Serial.println(data);
  }

}

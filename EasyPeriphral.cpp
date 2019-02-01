#include <LBLE.h>
#include <CLBLEPeriphral.h>
#include "Arduino.h"
#include "EasyPeriphral.h"

const char* serviceUUID = "00001802-0000-1000-8000-00805f9b34fb";
const char* rxUUID      = "00002a04-0000-1000-8000-00805f9b34fb";
const char* txUUID      = "00002a05-0000-1000-8000-00805f9b34fb";
char* name = "LBLE-A";

LBLEUuid uuid(serviceUUID);
LBLEService uartService(serviceUUID);
LBLECharacteristicString rxCharacteristic(rxUUID, LBLE_READ | LBLE_WRITE);//Rx
LBLECharacteristicString txCharacteristic(txUUID, LBLE_READ | LBLE_WRITE);//Tx

EasyPeriphral::EasyPeriphral(){
  uartService.addAttribute(rxCharacteristic);
  uartService.addAttribute(txCharacteristic);
  LBLEPeripheral.addService(uartService);
}
EasyPeriphral::~EasyPeriphral(){/*nothing to do here*/}

void EasyPeriphral::begin(){
  CLBLEAdvertisementData advertisement;
  advertisement.configAsConnectableDevice(name, serviceUUID);

  LBLEPeripheral.setName(name);
  LBLEPeripheral.advertise(advertisement);
  LBLEPeripheral.begin();
}

void EasyPeriphral::setDeviceName(char* devName){
    name = devName;
}

void EasyPeriphral:broadcast(int_16_t number){
    CLBLEAdvertisementData advertisement;
    advertisement.configAsConnectableWithPayload(name, serviceUUID, number);
    LBLEPeripheral.stopAdvertise();
    LBLEPeripheral.advertise(advertisement);
}
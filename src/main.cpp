#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEAdvertisedDevice.h>

#define SCAN_INTERVAL 100
#define SCAN_WINDOW 99
#define SCAN_TIME 5
BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice)  {
    }
};


void setup() {
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(SCAN_INTERVAL);
  pBLEScan->setWindow(SCAN_WINDOW);
  Serial.begin(115200);
}

void loop() {
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME, false);
  int count = foundDevices.getCount();
  for (int i = 0; i < count; i++) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    Serial.println(device.getAddress().toString().c_str());
  }
}
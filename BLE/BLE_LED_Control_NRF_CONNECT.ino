// This code is developed for PG-DESD Students at ACTS Pune.
// Use Case: This program demonstrates BLE (Bluetooth Low Energy) communication using an ESP32 microcontroller. 
// It allows a BLE-enabled client device to control an LED connected to the ESP32 by sending specific commands ('1' to turn ON, '0' to turn OFF).
// It is useful for learning IoT device communication and embedded system concepts.
// Developed and maintained by: bhupendra.jmd@gmail.com
// Use the NRF Connect app to control it.
// The data shall be sent in the form of UTF-8 string format.

#include <BLEDevice.h>  // Include BLEDevice library for BLE functionalities
#include <BLEServer.h>  // Include BLEServer library to create a BLE server
#include <BLEUtils.h>  // Include BLEUtils library for BLE utility functions
#include <BLE2902.h>  // Include BLE2902 library for adding descriptors

#define LED_PIN 2  // Define the GPIO pin connected to the internal LED

// Declare BLE server and characteristic pointers
BLEServer *pServer = nullptr;  // Pointer to the BLE server instance
BLECharacteristic *pCharacteristic = nullptr;  // Pointer to the BLE characteristic instance

// Declare flags to track connection status and LED state
bool deviceConnected = false;  // Flag to check if a BLE device is connected
bool ledState = false;  // Flag to store the current state of the LED (ON/OFF)
String lastValue = "";  // Variable to store the last received value

// Define unique identifiers for the BLE service and characteristic
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"  // UUID for the BLE service (replace with your own UUID)
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-1234567890ab"  // UUID for the BLE characteristic (replace with your own UUID)

// Define a class to handle server callbacks for device connection and disconnection events
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;  // Set the deviceConnected flag to true
    Serial.println("Device connected.");  // Print a message to indicate connection
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;  // Set the deviceConnected flag to false
    Serial.println("Device disconnected.");  // Print a message to indicate disconnection
    BLEDevice::getAdvertising()->start();  // Restart BLE advertising to allow reconnection
    Serial.println("Restarting advertising...");  // Print a message about advertising restart
  }
};

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate for debugging

  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as an output pin

  Serial.println("Initializing BLE...");  // Print initialization message
  BLEDevice::init("ESP32_LED_Control");  // Initialize BLE with the device name "ESP32_LED_Control"
  pServer = BLEDevice::createServer();  // Create a BLE server instance
  pServer->setCallbacks(new MyServerCallbacks());  // Attach the server callback to handle connection events

  BLEService *pService = pServer->createService(SERVICE_UUID);  // Create a BLE service with the specified UUID

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ
                    );  // Create a BLE characteristic with read and write properties

  pCharacteristic->addDescriptor(new BLE2902());  // Add a descriptor to the characteristic

  pService->start();  // Start the BLE service

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();  // Get the advertising object
  pAdvertising->start();  // Start advertising the BLE service

  Serial.println("BLE is ready. Waiting for a connection...");  // Print a message indicating BLE readiness
}

void loop() {
  if (deviceConnected) {  // Check if a BLE device is connected
    String value = pCharacteristic->getValue().c_str();  // Get the value sent by the client and convert it to a String

    if (value.length() > 0 && value != lastValue) {  // Check if a new valid value is received
      lastValue = value;  // Update the lastValue with the current value

      Serial.print("Received Value: ");  // Print the received value
      Serial.println(value);  // Print the value in a new line

      if (value == "1" && !ledState) {  // If the value is "1" and LED is currently OFF
        Serial.println("Turning LED ON...");  // Print message about turning LED on
        digitalWrite(LED_PIN, HIGH);  // Set the LED pin HIGH to turn on the LED
        ledState = true;  // Update the LED state to ON
      } else if (value == "0" && ledState) {  // If the value is "0" and LED is currently ON
        Serial.println("Turning LED OFF...");  // Print message about turning LED off
        digitalWrite(LED_PIN, LOW);  // Set the LED pin LOW to turn off the LED
        ledState = false;  // Update the LED state to OFF
      } else if (value != "1" && value != "0") {
        Serial.print("Invalid value received: ");  // Print the invalid value received
        Serial.println(value);  // Print the actual invalid value
        Serial.println("Please send '1' or '0'.");  // Print error for invalid values
      }

      Serial.print("Current LED State: ");  // Print the current state of the LED
      Serial.println(ledState ? "ON" : "OFF");  // Print "ON" or "OFF" based on the ledState flag
    }
  } else {
    Serial.println("No device connected. Waiting...");  // Print message indicating no device is connected
    delay(1000);  // Add a delay to reduce spamming of logs
  }
}

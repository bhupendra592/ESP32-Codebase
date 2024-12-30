/*
 * MQTT Code for CDAC Students to Subscribe to Topics for LED Control
 * MQTT Subscriber for Event-Based Communication
 * Uses PubSubClient and ArduinoJson library for MQTT functionality
 * Install Libraries: PubSubClient by Nick O'Leary and ArduinoJson by Benoît Blanchon
 *
 * Documentation Reference:
 * 1. PubSubClient: https://pubsubclient.knolleary.net/
 * 2. ArduinoJson: https://arduinojson.org/v6/doc/
 * 3. WiFi Library: https://www.arduino.cc/en/Reference/WiFi
 * 4. ESP-IDF WiFi MAC API: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html
 *
 * Use Case:
 * This application demonstrates MQTT communication to control an LED based on "ON" and "OFF" commands.
 *
 * Contact: bhupendra.jmd@gmail.com
 */

#include "mqtt_config.h"  // Include constants from header file
#include <WiFi.h>
#include <PubSubClient.h>
#include <esp_wifi.h>  // Include ESP32 WiFi library for MAC address spoofing

WiFiClient wifiClient;  // WiFi client for ESP32
PubSubClient mqttClient(wifiClient);  // MQTT client

unsigned long lastReconnectAttemptTime = 0;  // Timestamp for last reconnect attempt
uint8_t customMacAddress[] = CUSTOM_MAC_ADDRESS;

/*
 * Callback Function: handleIncomingCommand
 * Description: Processes messages received from the subscribed MQTT topic.
 * Parameters:
 * - topic: The MQTT topic from which the message was received.
 * - payload: The message payload as a byte array.
 * - length: Length of the payload array.
 * Behavior:
 * - If the message is "ON", the built-in LED is turned on.
 * - If the message is "OFF", the built-in LED is turned off.
 * - Logs unknown commands for debugging purposes.
 */
void handleIncomingCommand(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message on topic: ");
  Serial.println(topic);

  String commandMessage;
  for (unsigned int i = 0; i < length; i++) {
    commandMessage += (char)payload[i];
  }
  Serial.print("Command message: ");
  Serial.println(commandMessage);

  // Control LED based on the received command
  if (commandMessage == "ON") {
    digitalWrite(LED_BUILTIN_PIN, HIGH);
    Serial.println("LED turned ON");
  } else if (commandMessage == "OFF") {
    digitalWrite(LED_BUILTIN_PIN, LOW);
    Serial.println("LED turned OFF");
  } else {
    Serial.println("Unknown command received");
  }
}

/*
 * Function: reconnectToBroker
 * Description: Reconnects to the MQTT broker and subscribes to the COMMAND_TOPIC.
 * Behavior:
 * - Attempts to connect using client credentials defined in mqtt_config.h.
 * - Subscribes to the COMMAND_TOPIC upon successful connection.
 * - Logs connection and subscription status.
 * Returns:
 * - true: If successfully connected and subscribed.
 * - false: If connection or subscription fails.
 */
bool reconnectToBroker() {
  //if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) - uncomment this line and comment below on case username and password based auth is there
  if (mqttClient.connect(MQTT_CLIENT_ID)) {
    Serial.println("Connected to MQTT Broker.");
    // Subscribe to the command topic
    if (mqttClient.subscribe(COMMAND_TOPIC)) {
      Serial.println("Successfully subscribed to command topic.");
    } else {
      Serial.println("Failed to subscribe to command topic.");
    }
  } else {
    Serial.print("Failed to connect to MQTT Broker. Error code: ");
    Serial.println(mqttClient.state());
  }
  return mqttClient.connected();
}

void setup() {
  Serial.begin(115200);  // Start serial communication for debugging
  pinMode(LED_BUILTIN_PIN, OUTPUT);  // Set built-in LED as output
  digitalWrite(LED_BUILTIN_PIN, LOW);  // Ensure LED is off initially

  Serial.println("Initializing WiFi connection...");

  // Set WiFi mode to Station
  WiFi.mode(WIFI_STA);

  // Set custom MAC address
  esp_wifi_set_mac(WIFI_IF_STA, customMacAddress);

  // Connect to WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait until WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Configure MQTT client
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(handleIncomingCommand);
  lastReconnectAttemptTime = 0;
}

void loop() {
  unsigned long currentTime = millis();

  // Reconnect to the MQTT broker if disconnected
  if (!mqttClient.connected()) {
    if (currentTime - lastReconnectAttemptTime > 5000) {
      lastReconnectAttemptTime = currentTime;
      if (reconnectToBroker()) {
        lastReconnectAttemptTime = 0;
      }
    }
  } else {
    mqttClient.loop();  // Maintain MQTT connection
  }
}

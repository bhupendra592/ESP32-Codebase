# Steps to Control LED using Mosquitto_pub

This guide demonstrates how to set up an ESP8266 and use the `mosquitto_pub` utility to control an LED via MQTT messages. The setup assumes you are using Ubuntu 20.04 and have Mosquitto installed as your MQTT broker.

## Prerequisites

1. **Ubuntu 20.04**
2. **ESP8266 Development Board**
3. **Mosquitto MQTT Broker and Client Tools** installed
   - To install Mosquitto:
     ```bash
     sudo apt update
     sudo apt install -y mosquitto mosquitto-clients
     ```
4. Arduino IDE installed (download from [Arduino Official Website](https://www.arduino.cc/en/software)).
5. Required Arduino Libraries:
   - **PubSubClient** by Nick O'Leary
   - **ArduinoJson** by Benoît Blanchon

---

## Steps

### 1. Set Up the ESP8266

#### Step 1.1: Install ESP8266 Board Support in Arduino IDE
1. Open Arduino IDE and go to `File > Preferences`.
2. In the **Additional Boards Manager URLs**, add the following:
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Go to `Tools > Board > Boards Manager`.
4. Search for `ESP8266` and click **Install**.

#### Step 1.2: Install Required Libraries
1. Go to `Sketch > Include Library > Manage Libraries`.
2. Search for and install:
   - **PubSubClient**
   - **ArduinoJson**

#### Step 1.3: Prepare the Code
1. Copy the provided code (`mqtt_config.h` and main `.ino` file) into a new Arduino project.
2. Modify `mqtt_config.h` with your WiFi and MQTT broker details:
   ```c
   #define WIFI_SSID "Your_WiFi_Name"      // Replace with your WiFi SSID
   #define WIFI_PASSWORD "Your_WiFi_Password"  // Replace with your WiFi password
   #define COMMAND_TOPIC "cvr/fdp/ledcontrol"  // MQTT topic to subscribe
   #define MQTT_BROKER "test.mosquitto.org"    // Replace with your MQTT broker
   ```

#### Step 1.4: Upload the Code
1. Connect the ESP8266 to your computer via USB.
2. Select the correct board and port under `Tools > Board` and `Tools > Port`.
3. Click the **Upload** button to flash the code onto the ESP8266.

---

### 2. Connect the LED to the ESP8266
1. Connect the LED's **Anode (+)** to GPIO2 (D4 on NodeMCU).
2. Connect the LED's **Cathode (-)** to GND.

---

### 3. Start Mosquitto Broker

#### Step 3.1: Start the Broker
Start the Mosquitto broker on the default port (1883):
```bash
sudo systemctl start mosquitto
```

To ensure the broker starts automatically on boot:
```bash
sudo systemctl enable mosquitto
```

#### Step 3.2: Verify the Broker is Running
Check the service status:
```bash
sudo systemctl status mosquitto
```

---

### 4. Test MQTT Communication

#### Step 4.1: Test Using Mosquitto Clients
1. Open a terminal and subscribe to the test topic:
   ```bash
   mosquitto_sub -h test.mosquitto.org -t "cvr/fdp/ledcontrol"
   ```
2. Open another terminal and publish a test message:
   ```bash
   mosquitto_pub -h test.mosquitto.org -t "cvr/fdp/ledcontrol" -m "Hello LED!"
   ```

If the setup is correct, the message should appear in the subscriber terminal.

---

### 5. Control the LED

To control the LED on the ESP8266, publish the following commands to the MQTT topic `cvr/fdp/ledcontrol`:

#### Step 5.1: Turn ON the LED
```bash
mosquitto_pub -h test.mosquitto.org -t "cvr/fdp/ledcontrol" -m "ON"
```

#### Step 5.2: Turn OFF the LED
```bash
mosquitto_pub -h test.mosquitto.org -t "cvr/fdp/ledcontrol" -m "OFF"
```

#### Step 5.3: Verify the Commands
Monitor the LED on the ESP8266 and ensure it responds correctly to the commands. Additionally, you can check the Serial Monitor of the ESP8266 to view logs of received messages.

---

### 6. Troubleshooting

#### LED Does Not Respond
- Ensure the ESP8266 is connected to the same WiFi network as specified in the `mqtt_config.h` file.
- Verify the MQTT broker address and port are correct.
- Ensure the correct GPIO pin is configured for the LED in `mqtt_config.h`.

#### Mosquitto Not Running
- Restart the Mosquitto service:
  ```bash
  sudo systemctl restart mosquitto
  ```
- Check for errors in the Mosquitto logs:
  ```bash
  sudo journalctl -u mosquitto
  ```

---

## Conclusion

You have successfully set up the ESP8266 and controlled an LED using the `mosquitto_pub` utility to send MQTT messages. This setup can be expanded for other IoT applications requiring MQTT-based communication.


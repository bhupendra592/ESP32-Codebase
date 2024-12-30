
# **FPCS: MQTT LED Control with ESP32**

This project demonstrates MQTT-based LED control using an ESP32 microcontroller. The ESP32 subscribes to MQTT topics to turn the LED **ON** or **OFF** based on received commands.

---

## **Features**

- **Functionality**: Controls an LED via MQTT commands.
- **MQTT Publish/Subscribe**: Listens to MQTT topics for commands.
- **Control**: Supports **ON** and **OFF** commands to toggle the LED.

---

## **Prerequisites**

### Hardware
1. ESP32 microcontroller.
2. Built-in or external LED connected to the ESP32.

### Software
1. Arduino IDE with ESP32 board support.
2. Required Libraries:
   - **PubSubClient**: For MQTT functionality.
   - **WiFi**: For ESP32 network connectivity.
3. MQTT Broker (e.g., Mosquitto).

---

## **Setup Instructions**

### 1. Install Required Libraries
In the Arduino IDE:
- Go to `Sketch` > `Include Library` > `Manage Libraries`.
- Search for and install:
  - **PubSubClient** by Nick O'Leary.

---

### 2. Configure the Code
1. Open the provided code in the Arduino IDE.
2. Update the following placeholders in `mqtt_config.h`:
   - `WIFI_SSID`: Your WiFi network name.
   - `WIFI_PASSWORD`: Your WiFi password.
   - `MQTT_BROKER`: IP address or hostname of your MQTT broker.
   - `COMMAND_TOPIC`: MQTT topic for receiving LED control commands.

---

### 3. Upload Code to ESP32
1. Connect the ESP32 to your computer via USB.
2. Select the correct **Board** (`Tools > Board > ESP32 Dev Module`) and **Port**.
3. Click the **Upload** button to flash the code onto the ESP32.

---

### 4. Set Up MQTT Broker
1. Install Mosquitto or another MQTT broker:
   - [Mosquitto Installation Guide](https://mosquitto.org/download/).
2. Start the broker on your local machine:
   ```bash
   mosquitto
   ```

---

### 5. Control the LED
Use the `mosquitto_pub` command to send messages to the ESP32:
- **Turn LED ON**:
  ```bash
  mosquitto_pub -h <BROKER_IP> -t <COMMAND_TOPIC> -m "ON"
  ```
- **Turn LED OFF**:
  ```bash
  mosquitto_pub -h <BROKER_IP> -t <COMMAND_TOPIC> -m "OFF"
  ```

---

## **Troubleshooting**

1. **ESP32 not connecting to WiFi:**
   - Double-check your `WIFI_SSID` and `WIFI_PASSWORD`.
   - Ensure the WiFi network is within range.

2. **ESP32 not responding to MQTT commands:**
   - Verify that the MQTT broker is running.
   - Ensure the MQTT topic matches the `COMMAND_TOPIC` in the code.
   - Check that the ESP32 is connected to the same network as the MQTT broker.

3. **Command not working:**
   - Ensure the payload is either `ON` or `OFF` in UTF-8 string format.

---

## **Additional Resources**

- [Mosquitto Documentation](https://mosquitto.org/documentation/)
- [MQTT Protocol Overview](http://mqtt.org/)

---

Enjoy exploring MQTT and IoT! 🎉
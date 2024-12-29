# Steps to Use the ESP32 LED Control Program with the NRF Connect App

This guide explains how to compile, upload, and execute the ESP32 LED control program and use the NRF Connect app to control the LED.

## Requirements
- ESP32 microcontroller
- Arduino IDE (configured for ESP32)
- NRF Connect app (available on Android and iOS)
- USB cable for ESP32
- A computer with Arduino IDE installed

## Steps

### 1. Clone the Repository
1. Clone the repository containing the ESP32 LED control program:
   ```bash
   git clone https://github.com/bhupendra592/ESP32-Codebase
   cd ESP32-Codebase
   ```

### 2. Open the Code in Arduino IDE
1. Open Arduino IDE.
2. Navigate to `File > Open` and select the `ESP32_LED_Control.ino` file from the cloned repository.

### 3. Configure the Arduino IDE for ESP32
1. Add the ESP32 board to the Arduino IDE if not already added:
   - Go to `File > Preferences`.
   - Add the following URL to the "Additional Board Manager URLs":
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Click "OK."
2. Install the ESP32 board package:
   - Go to `Tools > Board > Boards Manager`.
   - Search for `ESP32` and click "Install."
3. Select the ESP32 board:
   - Go to `Tools > Board` and choose your ESP32 board model (e.g., "ESP32 Dev Module").
4. Select the appropriate port:
   - Go to `Tools > Port` and choose the port to which your ESP32 is connected.

### 4. Upload the Code to ESP32
1. Connect the ESP32 to your computer via USB.
2. Click the "Upload" button in Arduino IDE (the arrow icon).
3. Wait for the code to compile and upload to the ESP32. Ensure you see "Done uploading" in the console.

### 5. Verify BLE Advertisement
1. Open the Serial Monitor in Arduino IDE (`Tools > Serial Monitor`).
2. Set the baud rate to `115200`.
3. Verify that the ESP32 is advertising as `ESP32_LED_Control`.

### 6. Connect Using the NRF Connect App
1. Open the NRF Connect app on your smartphone.
2. Scan for nearby BLE devices.
3. Locate and connect to the device named `ESP32_LED_Control`.

### 7. Control the LED
1. Navigate to the "GATT" (Generic Attribute Profile) section in the NRF Connect app.
2. Identify the custom service with UUID `12345678-1234-1234-1234-123456789abc`.
3. Locate the characteristic with UUID `abcd1234-ab12-cd34-ef56-1234567890ab`.
4. Write the following values to control the LED:
   - `1` (UTF-8) to turn ON the LED.
   - `0` (UTF-8) to turn OFF the LED.
5. Observe the LED state change on the ESP32 and the log messages on the Serial Monitor.

### 8. Disconnect from the Device
1. Disconnect from the ESP32 using the NRF Connect app.
2. Observe that the ESP32 restarts BLE advertising automatically.

## Troubleshooting
- **Device not found in NRF Connect:** Ensure the ESP32 is powered and BLE advertising is active.
- **Cannot upload code:** Check that the correct port and board are selected in the Arduino IDE.
- **Invalid value error:** Ensure the value is sent as a UTF-8 string.

## Notes
- This program is developed for PG-DESD students at ACTS Pune.
- Developed and maintained by: bhupendra.jmd@gmail.com.

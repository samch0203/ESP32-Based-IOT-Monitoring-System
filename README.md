# ESP32-Based IoT Monitoring System

## Overview

The ESP32-Based IoT Monitoring System is an Internet of Things (IoT) project designed to monitor environmental conditions using an ESP32 microcontroller and a DHT22 temperature and humidity sensor.

The system collects environmental data, processes sensor readings, and displays the information through a web-based monitoring dashboard using Wi-Fi and HTTP communication.

## Objectives

- Develop a sensor-based IoT monitoring system.
- Interface the DHT22 sensor with the ESP32 microcontroller.
- Collect temperature and humidity readings.
- Establish Wi-Fi connectivity for remote monitoring over the local network.
- Display real-time sensor information through a web dashboard.
- Understand HTTP communication in IoT applications.

## Hardware Requirements

| Component | Quantity |
|---|---|
| ESP32 Development Board | 1 |
| DHT22 Sensor | 1 |
| Breadboard | 1 |
| Jumper Wires | 3 |
| 10kΩ Resistor | 1 (if required) |

## Software Requirements

- Arduino IDE
- ESP32 Board Package
- Adafruit DHT Sensor Library
- Adafruit Unified Sensor Library
- Web Browser

## Technologies Used

- C++
- ESP32
- DHT22
- Arduino IDE
- Wi-Fi
- HTTP
- HTML
- CSS
- JavaScript

## Circuit Connections

| DHT22 Sensor | ESP32 |
|---|---|
| VCC | 3.3V |
| DATA | GPIO 4 |
| GND | GND |

Note: A bare DHT22 sensor requires a 10kΩ pull-up resistor between DATA and VCC. Some sensor modules include this resistor.

## Project Structure

```text
ESP32-IoT-Monitoring-System/
│
├── esp32_iot_monitor.ino
│
├── README.md
│
└── screenshots/
    ├── serial-monitor.png
    └── dashboard.png
```

## Installation and Setup

### 1. Clone the Repository

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

### 2. Install Required Libraries

Open Arduino IDE and install:

- DHT sensor library by Adafruit
- Adafruit Unified Sensor

### 3. Configure Wi-Fi

Open `esp32_iot_monitor.ino` and enter your Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

Do not publish your actual Wi-Fi credentials on GitHub.

### 4. Upload the Code

- Connect ESP32 to your computer.
- Select the ESP32 board.
- Select the appropriate COM port.
- Upload the Arduino sketch.

### 5. Access the Monitoring Dashboard

Open Serial Monitor at 115200 baud.

Copy the IP address displayed by the ESP32 and open it in a browser connected to the same Wi-Fi network.

Example:

```text
http://192.168.1.105
```

## API Endpoint

The project provides an HTTP endpoint for retrieving sensor data.

**Endpoint:**

```text
GET /api/data
```

**Example JSON Response:**

```json
{
  "status": "success",
  "temperature": 28.5,
  "humidity": 65.2
}
```

The example values are illustrative.

## Working Principle

1. The DHT22 sensor measures temperature and humidity.
2. ESP32 reads the sensor measurements.
3. ESP32 establishes a Wi-Fi connection.
4. The ESP32 HTTP server makes sensor readings available.
5. The web dashboard retrieves updated values every two seconds.
6. Users monitor environmental conditions through a browser.

## Results

The expected system behavior includes:

- Successful ESP32 Wi-Fi connection.
- Periodic temperature and humidity acquisition.
- HTTP-based sensor data retrieval.
- JSON-formatted API responses.
- Browser-based environmental monitoring.

Add actual hardware photographs and screenshots of your working dashboard in the `screenshots/` folder.

## Applications

- Environmental monitoring
- Smart agriculture
- Greenhouse monitoring
- Industrial environment monitoring
- IoT-based automation systems
- Remote temperature and humidity monitoring

## Future Enhancements

- MQTT-based communication.
- Cloud data storage and visualization.
- Historical sensor data analysis.
- Mobile application integration.
- Temperature and humidity threshold alerts.
- Integration with additional sensors.

## Author

**Samiksha Chibade**

B.E. Artificial Intelligence & Data Science

[LinkedIn](https://www.linkedin.com/in/samiksha-chibade-041702398/) | [GitHub](https://github.com/samch0203)

---

*This project demonstrates practical implementation of ESP32, sensor interfacing, Wi-Fi connectivity, HTTP communication, and IoT-based environmental monitoring.*

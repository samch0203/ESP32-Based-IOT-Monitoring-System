
#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// DHT22 configuration
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Web server on port 80
WebServer server(80);

float temperature = 0;
float humidity = 0;

unsigned long previousMillis = 0;
const unsigned long interval = 2000;

// HTML monitoring dashboard
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 IoT Monitor</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            font-family: Arial;
            text-align: center;
            background: #eef2f3;
            margin-top: 50px;
        }
        .card {
            background: white;
            padding: 25px;
            margin: 20px auto;
            width: 260px;
            border-radius: 12px;
            box-shadow: 0 3px 10px #bbb;
        }
        h1 { color: #174a70; }
        .value {
            font-size: 32px;
            color: #159b78;
            font-weight: bold;
        }
    </style>
</head>
<body>

<h1>ESP32 IoT Monitoring System</h1>

<div class="card">
    <h2>Temperature</h2>
    <p class="value" id="temp">-- °C</p>
</div>

<div class="card">
    <h2>Humidity</h2>
    <p class="value" id="humid">-- %</p>
</div>

<p id="status">Connecting...</p>

<script>
async function updateData() {
    try {
        const response = await fetch('/api/data');
        const data = await response.json();

        if (data.status !== "success") {
            throw new Error("Sensor reading unavailable");
        }

        document.getElementById("temp").innerText =
            data.temperature + " °C";

        document.getElementById("humid").innerText =
            data.humidity + " %";

        document.getElementById("status").innerText =
            "Live sensor data received";

    } catch (error) {
        document.getElementById("status").innerText =
            "Unable to retrieve sensor data";
    }
}

updateData();
setInterval(updateData, 2000);
</script>

</body>
</html>
)rawliteral";

// Read sensor values
void readSensor() {
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {
        temperature = t;
        humidity = h;
        Serial.println("Sensor data updated");
    } else {
        Serial.println("DHT22 sensor reading failed");
    }
}

// Main dashboard route
void handleRoot() {
    server.send_P(200, "text/html", webpage);
}

// JSON API route
void handleData() {
    String json;

    if (isnan(temperature) || isnan(humidity)) {
        json = "{\"status\":\"error\"}";
    } else {
        json = "{\"status\":\"success\",";
        json += "\"temperature\":" + String(temperature, 1) + ",";
        json += "\"humidity\":" + String(humidity, 1) + "}";
    }

    server.send(200, "application/json", json);
}

void setup() {
    Serial.begin(115200);

    dht.begin();

    Serial.println("Starting ESP32 IoT Monitor...");

    WiFi.begin(ssid, password);

    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Wi-Fi connected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    readSensor();

    server.on("/", handleRoot);
    server.on("/api/data", handleData);

    server.begin();

    Serial.println("HTTP server started!");
}

void loop() {
    server.handleClient();

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        readSensor();
    }
}

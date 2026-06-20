#include <WiFi.h>
#include <PubSubClient.h>

// Pin Configurations
#define PIR_PIN 14
#define LDR_PIN 34
#define LED_PIN 12

// Thresholds
const int DARK_THRESHOLD = 1500; // Adjust based on simulated LDR characteristics

// Network & Cloud Credentials
const char* ssid = "Wokwi-GUEST"; 
const char* password = "";
const char* mqtt_server = "broker.hivemq.com"; // Public MQTT broker for simulation

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_SmartHome_Client")) {
      Serial.println("connected");
    } else {
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int ldrValue = analogRead(LDR_PIN);
  int motionDetected = digitalRead(PIR_PIN);

  Serial.print("LDR Value: "); Serial.print(ldrValue);
  Serial.print(" | Motion: "); Serial.println(motionDetected);

  // Condition: Low-light (High resistance/Low voltage depends on wiring) AND Motion detected
  if (ldrValue > DARK_THRESHOLD && motionDetected == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("ALERT: Motion detected in dark!");
    client.publish("home/security/alerts", "ALERT: Unauthorized motion detected in a dark room!");
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(2000); // 2-second polling interval
}

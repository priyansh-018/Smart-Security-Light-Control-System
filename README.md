# Smart Security & Light Control System

## 1. Aim
To design, simulate, and implement an IoT-based Smart Home Automation system that intelligently controls lighting and sends real-time security alerts to a cloud platform by cross-referencing human movement with ambient light levels.

---

## 2. Problem Statement
Traditional home lighting and security systems operate independently, often leading to energy wastage or delayed intrusion responses. There is a need for an automated, integrated solution that:
* Continuously monitors room occupancy and ambient environmental lighting.
* Dynamically toggles illumination only when necessary (e.g., when a room is dark and occupied).
* Triggers immediate cloud-based security notifications when motion is detected in low-light conditions, signaling potential unauthorized presence in a dark environment.

---

## 3. Scope of the Solution
* **Energy Efficiency:** Automates light controls so they are active exclusively under dual conditions: low ambient light **and** human presence.
* **Intrusion Detection:** Acts as a localized security system during nighttime or in unlit, restricted areas.
* **Cloud Connectivity:** Bridges physical sensor telemetry with cloud brokers to enable remote monitoring and instant push notifications from anywhere in the world.
* **Scalability:** The simulated framework can be easily scaled up to use real hardware relays, high-voltage home appliances, and enterprise-grade IoT dashboards.

---

## 4. Required Components

| Category | Component Name | Purpose / Description |
| :--- | :--- | :--- |
| **Hardware** | ESP32 Microcontroller | Main controller with built-in Wi-Fi capabilities to process data and connect to the cloud. |
| **Hardware** | PIR Motion Sensor | Continuously detects human infrared movement in the monitored zone. |
| **Hardware** | LDR (Photoresistor) | Monitors ambient environmental light levels. |
| **Hardware** | LED & 220Ω Resistor | Simulates the smart light actuator that automatically turns on/off. |
| **Software** | Wokwi Simulator | The browser-based simulation engine used to wire and run the circuit. |
| **Software** | Arduino IDE Core / C++ | Used to write the firmware code logic. |
| **Software** | `PubSubClient` Library | Handles the MQTT messaging protocol to communicate with the cloud. |
| **Cloud** | HiveMQ Public Broker | The cloud MQTT broker used to route real-time security alert payloads. |

---

## 5. Flowchart of the Code

```text
       [Start Simulation]
               │
               ▼
   [Initialize Wi-Fi & MQTT Cloud]
   [Configure Pins: PIR=Input, LDR=Analog, LED=Output]
               │
               ▼
┌────────► [Read LDR Analog Value]
│          [Read PIR Digital State]
│              │
│              ▼
│     Is Room Dark (LDR > 1500) 
│               AND 
│     Is Motion Detected (PIR == HIGH)?
│              ├─── YES ───► [Turn ON LED / Smart Light]
│              │               │
│              │               ▼
│              │             [Publish "Security Alert" to Cloud via MQTT]
│              │               │
│              └─── NO ────► [Turn OFF LED / Keep Light Off]
│                              │
└──────────────────────────────┴───► [Wait 2 Seconds / Loop Again]

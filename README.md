# Care Cane  
**“Seeing Beyond Boundaries”**

---

## 🚀 Project Overview
**Care Cane** is a smart white cane designed to empower visually impaired users with real-time obstacle detection, navigation assistance, fall detection, and emergency alerts. Branded under the tagline **“Seeing Beyond Boundaries”**, Care Cane combines cutting-edge sensor technologies, wireless connectivity, and a custom PCB & casing to deliver a seamless, reliable experience.

---

## 🔑 Key Features

- **Obstacle Detection & Avoidance**  
  - Two ultrasonic sensors positioned for low- and mid-height obstacles  
  - Haptic feedback via vibration motors and auditory alerts via buzzer  

- **Navigation Assistance**  
  - GPS module for real-time location tracking  
  - SIM900A module for remote data/SMS alerts (e.g., fall detection)  
  - Bluetooth connectivity for smartphone integration and voice guidance  
  - Turn-by-turn directions delivered as haptic pulses and voice prompts  

- **Fall Detection & Emergency Assistance**  
  - Accelerometer & gyroscope detect sudden movements and falls  
  - SIM900A module sends automated SMS with GPS coordinates and custom alert message to predefined emergency contacts if the cane remains stationary beyond a set threshold  
  - Built-in buzzer and LED light pattern activate to attract nearby assistance  

- **Environmental Sensing**  
  - Ambient light sensor adjusts any visual indicators for optimal visibility  

- **Audio Feedback**  
  - Built-in speaker provides auditory feedback for navigation cues, obstacle alerts, and system status  

---

## 🛠️ Hardware Components

| Component               | Purpose                                                      |
|-------------------------|--------------------------------------------------------------|
| ESP32 module            | Main microcontroller & connectivity hub                      |
| GPS module              | Real-time location tracking                                  |
| SIM900A module          | SMS alerts & remote emergency communication                  |
| Ultrasonic sensors (×2) | Obstacle detection at multiple heights                       |
| Accelerometer & Gyro    | Fall detection                                               |
| Ambient Light Sensor    | Auto-adjust visual indicators                                |
| Vibration motors (×2)   | Haptic feedback                                              |
| Buzzer                  | Audible alerts                                               |
| Speaker                 | Audio feedback                                               |

---

## 🏗️ System Architecture

1. **Sensor Layer**  
   - Ultrasonic sensors → ESP32  
   - Accelerometer/gyro → ESP32  
   - Ambient light sensor → ESP32  

2. **Processing & Control**  
   - ESP32 runs obstacle-avoidance, fall-detection, and control firmware  
   - Custom PCB integrates power regulation, sensor hookups, and module slots  

3. **Connectivity & Feedback**  
   - GPS & SIM900A modules communicate over UART  
   - Bluetooth connects to smartphone app for map display & voice guidance  
   - Haptic (vibration) & audio (buzzer/speaker) outputs  
   - LED light pattern for emergency alert  

---

## 📐 PCB & Mechanical Design

- **Custom PCB**  
  - Single-layer PCB designed in KiCad/Altium  
  - Integrated power-saving circuitry to extend battery life  
  - Modular slots for easy swapping of GPS/SIM900A modules  

- **Casing & 3D Printing**  
  - Ergonomic handle with built-in vibration motors, buzzer, speaker, and LED indicator  
  - Lightweight ABS housing for electronics  
  - Snap-fit design for tool-less assembly  

- **Packaging & User Manual**  
  - Eco-friendly cardboard box with foam inserts  
  - Illustrated quick-start guide and full user manual included  

---

## 🏗️ Prototype Assembly

1. **PCB Assembly**  
   - Solder all SMT & through-hole components  
   - Verify power rails, test with multimeter  

2. **Module Connections**  
   - Plug in GPS & SIM900A modules into their headers  
   - Connect ultrasonic sensors to GPIO pins  

3. **Casing Integration**  
   - Insert PCB into 3D-printed housing  
   - Snap on front/back shells; secure with plastic clips  

4. **Final Testing**  
   - Power on, run system-check firmware  
   - Walk test for obstacle alerts  
   - Simulate fall and verify SMS + audio/LED alert  

---

## 📲 Smartphone App & Google Maps Integration

1. **GPS → Arduino**  
   - TinyGPS++ library reads coordinates  

2. **Bluetooth Link**  
   - HC-05/ESP32 BLE sends data to Android app  

3. **Google Maps API**  
   - Displays real-time position  
   - User sets destination; app calculates route  

4. **Haptic/Audio Cues**  
   - App sends “left/right/straight” commands back over Bluetooth  
   - Cane vibrates/buzzes in pattern  

---

# 🏠 Smart Home Controller Using ESP32

## 📌 Project Overview

The **Smart Home Controller** is an IoT-based embedded system designed to automate and monitor different functions of a home.

The system uses an **ESP32** as the main controller and integrates sensors, LEDs, relay modules, buttons, a buzzer, and an I2C LCD to provide automatic and manual control.

The project is developed and tested using the **Wokwi online simulator**.

---

## 🎯 Objectives

- Automate room lighting based on motion and light intensity.
- Automatically control the fan based on temperature.
- Detect human motion using a PIR sensor.
- Provide a security alert when motion is detected in security mode.
- Provide manual override controls for light and fan.
- Display system status and sensor readings on an LCD.
- Demonstrate an IoT-based smart home automation concept.

---

## ✨ Features

### 💡 Automatic Lighting
The room light is automatically controlled according to:
- PIR motion detection
- LDR/light intensity

### 🌡️ Temperature-Based Fan Control
The DHT22 sensor measures temperature.

When the temperature crosses the defined threshold, the fan control is activated automatically through the relay.

### 🚶 Motion Detection
The PIR sensor detects human movement inside the room.

### 🚨 Security Alert
A security mode can be enabled using the security button.

When security mode is active and motion is detected:
- Red LED turns ON
- Buzzer is activated
- Security alert is displayed on the LCD

### 🎛️ Manual Override
Manual buttons are provided for:
- Security Mode
- Manual Light Control
- Manual Fan Control

This allows the user to control the system manually when required.

### 📟 LCD Status Display
The I2C LCD displays important information such as:
- Temperature
- Motion status
- Light status
- Fan status
- Security status
- Alarm status

---

## 🧰 Components Used

| Component | Quantity |
|---|---:|
| ESP32 DevKit V1 | 1 |
| PIR Motion Sensor | 1 |
| Photoresistor (LDR) | 1 |
| DHT22 Temperature & Humidity Sensor | 1 |
| Relay Module | 2 |
| LED – Yellow/White (Room Light) | 1 |
| LED – Blue (Fan) | 1 |
| LED – Red (Security Alert) | 1 |
| LED – Green (System Status) | 1 |
| Buzzer | 1 |
| Push Button | 3 |
| LCD1602 I2C | 1 |
| 220Ω Resistor | 4 |

---

## 🔌 Pin Configuration

| Component | ESP32 GPIO |
|---|---|
| PIR OUT | GPIO 13 |
| LDR AO | GPIO 34 |
| DHT22 Data | GPIO 14 |
| Light Relay IN | GPIO 25 |
| Fan Relay IN | GPIO 26 |
| Buzzer | GPIO 27 |
| Security LED | GPIO 32 |
| System Status LED | GPIO 33 |
| Manual Light Button | GPIO 16 |
| Manual Fan Button | GPIO 17 |
| Security Button | GPIO 4 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

### Power Connections

- Sensors are powered according to their required voltage.
- ESP32 GND is used as the common ground.
- LCD uses I2C communication.
- LEDs are connected through 220Ω current-limiting resistors.

---

## 🏗️ System Architecture

The ESP32 acts as the central controller.

### Input Devices
- PIR Motion Sensor
- LDR
- DHT22
- Security Button
- Manual Light Button
- Manual Fan Button

### Processing Unit
- ESP32 DevKit V1

### Output Devices
- Room Light LED / Relay
- Fan LED / Relay
- Security LED
- System Status LED
- Buzzer
- LCD1602 I2C

### Working Flow

Sensors and buttons → ESP32 → Decision Making → Relays / LEDs / Buzzer / LCD

---

## ⚙️ Working Principle

1. The ESP32 initializes all sensors, buttons, outputs, and the LCD.
2. The PIR sensor continuously checks for human motion.
3. The LDR measures the surrounding light intensity.
4. The DHT22 measures temperature and humidity.
5. Based on motion and light intensity, the automatic lighting system controls the room light.
6. Based on temperature, the fan control is activated when required.
7. The security button enables or disables security mode.
8. When security mode is active and motion is detected, the security alarm is triggered.
9. Manual buttons allow the user to override automatic light and fan control.
10. The LCD continuously displays the current system status.
11. The green system LED indicates that the controller is running.

---

## 🔐 Security Logic

The security system works using the following logic:

```text
Security Mode OFF
       ↓
Normal Home Automation

Security Mode ON
       ↓
Motion Detected?
    ↙       ↘
  NO         YES
  ↓           ↓
Normal      Alarm ON
            ↓
       Red LED + Buzzer


🎛️ Manual Override Logic

The system supports manual control in addition to automatic operation.

Manual Light Button

Pressing the manual light button changes the light state manually.

Manual Fan Button

Pressing the manual fan button changes the fan state manually.

Security Button

Pressing the security button enables or disables security mode.

🖥️ Simulation

The complete project is simulated using Wokwi.

The simulation includes:

ESP32 DevKit V1
PIR sensor
LDR
DHT22
Relay modules
LEDs
Push buttons
Buzzer
I2C LCD

No physical breadboard is required for the Wokwi simulation.


📚 Libraries Used

The project uses the following Arduino libraries:

DHT sensor library
Adafruit Unified Sensor
LiquidCrystal I2C

These libraries are required for sensor and LCD operation.

🧪 Testing

The system was tested under different conditions:

Test Case	Expected Result
Motion detected in dark environment	Room light turns ON
No motion	Automatic light turns OFF when conditions are satisfied
High temperature	Fan turns ON
Normal temperature	Fan remains OFF
Security mode ON + motion	Red LED and buzzer activate
Security mode OFF + motion	No security alarm
Manual light button	Light state changes
Manual fan button	Fan state changes
System powered ON	Green status LED remains ON
Sensor values change	LCD updates system status

📸 Project Screenshots

The following screenshots can be included in the GitHub repository:

Complete Wokwi circuit
Normal system operation
Motion detected
Automatic light ON
Fan ON due to high temperature
Security mode enabled
Security alarm activated
LCD showing sensor/system status

🚀 Future Improvements

The project can be further improved by adding:

Wi-Fi based remote control
Mobile application
Web dashboard
IoT cloud monitoring
Voice control
Smart energy monitoring
Automatic scheduling
Multiple room control
Real AC appliance control using appropriate safety-rated hardware

🌟 Applications

This system can be used as a prototype for:

Smart homes
Home automation
Energy management
Security monitoring
IoT-based residential systems
Embedded systems learning

Author: Sonamika Anand Samrat
   B.Tech. – Computer Science & Engineering

License:
This project is created for educational and academic purposes.

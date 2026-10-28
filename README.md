# 🌐 ESP32 Wi-Fi Multisensor

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32"/>
  <img src="https://img.shields.io/badge/IDE-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino IDE"/>
  <img src="https://img.shields.io/badge/Project-IoT-purple?style=for-the-badge&logo=wifi&logoColor=white" alt="IoT"/>
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
</p>

<p align="center">
  <b>A hands-on IoT project for environmental monitoring, motion detection, and relay control using the ESP32.</b>
</p>

---

## ✨ Overview

The **ESP32 Wi-Fi Multisensor** is an Internet of Things (IoT) project developed using the Arduino IDE. It combines multiple sensors and output devices to monitor environmental conditions and provide relay control through a Wi-Fi web server.

## 🚀 Key Features

| Feature | Description |
|---|---|
| 🌡️ Temperature & Humidity | Measures environmental conditions using a DHT22 |
| 🚶 Motion Detection | Detects movement using a PIR sensor |
| 💡 Light Sensing | Detects ambient light using an LDR |
| ⚡ Relay Control | Controls an external circuit through a relay module |
| 🌈 RGB Status Indicator | Uses an RGB LED for status indication |
| 📡 Wi-Fi Connectivity | Connects the ESP32 to a wireless network |
| 🖥️ Web Server | Enables interaction through a web interface |

## 🧰 Hardware Components

- 🔹 ESP32 development board
- 🌡️ DHT22 temperature and humidity sensor
- 🚶 PIR motion sensor
- 💡 LDR and required circuit components
- ⚡ Relay module
- 🌈 RGB LED and current-limiting resistors
- 🔌 Breadboard, jumper wires, and USB cable

## 💻 Software & Technologies

<p>
  <img src="https://img.shields.io/badge/Arduino_IDE-00979D?style=flat-square&logo=arduino&logoColor=white" alt="Arduino IDE"/>
  <img src="https://img.shields.io/badge/ESP32-000000?style=flat-square&logo=espressif&logoColor=white" alt="ESP32"/>
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/Wi--Fi-IoT-blue?style=flat-square&logo=wifi&logoColor=white" alt="Wi-Fi"/>
</p>

- Arduino IDE
- ESP32 board support package
- Required sensor libraries
- Wi-Fi network for web-server access

## ⚙️ How It Works

1. The sensors collect environmental and motion-related data.
2. The ESP32 processes the sensor readings.
3. The configured operating mode determines how the relay and status indicator respond.
4. The ESP32 connects to Wi-Fi and hosts a web server.
5. A user can access the web interface using the ESP32's network address.

## 🔧 Getting Started

1. Install the Arduino IDE and ESP32 board support.
2. Connect the sensors and output devices according to your circuit diagram.
3. Install the libraries required by your sketch.
4. Add your Wi-Fi credentials to the code.
5. Upload the sketch to the ESP32.
6. Open the Serial Monitor to check connection details.
7. Open the web-server address provided by the ESP32.

## 🎯 Learning Objectives

- Understand ESP32 and IoT development.
- Interface multiple sensors with a microcontroller.
- Control output devices using a relay.
- Build a Wi-Fi-enabled web interface.
- Practice embedded programming with the Arduino IDE.

## 📚 Reference

Based on the multisensor project in *Learn ESP32 with Arduino IDE* by Rui Santos and Sara Santos.

> This repository documents my project implementation and learning experience. The original ebook is not included.

---

<p align="center">
  <b>🌱 Learning • Building • Innovating with IoT</b>
</p>

<p align="center">
  <i>Built with curiosity and the ESP32.</i>
</p>

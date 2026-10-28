# 🌐 ESP32 Wi-Fi Multisensor

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32"/>
  <img src="https://img.shields.io/badge/IDE-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino IDE"/>
  <img src="https://img.shields.io/badge/Project-IoT-purple?style=for-the-badge&logo=wifi&logoColor=white" alt="IoT"/>
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
</p>

<p align="center">
  <b>An IoT-based environmental monitoring and automatic control system built with ESP32 and Arduino IDE.</b>
</p>

---

## 📌 Project Overview

The **ESP32 Wi-Fi Multisensor** is a learning project that combines environmental sensing, motion detection, light-dependent automation, and relay control in a single ESP32-based system.

The system uses a DHT22 temperature and humidity sensor, a PIR motion sensor, and an LDR. An RGB LED indicates the selected operating mode, while a Wi-Fi web server provides a browser-based interface for monitoring and controlling the system.

## ✨ Key Features

▸ 🌡️ Temperature and humidity monitoring using DHT22

▸ 🚶 Motion detection using a PIR sensor

▸ 💡 Ambient light sensing using an LDR

▸ ⚡ Relay or output control

▸ 🌈 RGB LED status indication

▸ 📡 Wi-Fi connectivity and a browser-based control interface

▸ 💾 EEPROM-based storage of selected settings

▸ ⏱️ Adjustable timer and light threshold

## 🧰 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 development board | Main controller and Wi-Fi communication |
| DHT22 sensor | Temperature and humidity measurement |
| PIR motion sensor | Motion detection |
| LDR | Ambient light sensing |
| Relay module or compatible output circuit | Switching an external load |
| RGB LED | Operating-mode indication |
| Breadboard and jumper wires | Circuit connections |
| USB cable and suitable power supply | Programming and powering the board |

## 💻 Software and Libraries

◆ **Arduino IDE** - Writing and uploading the firmware

◆ **WiFi.h** - Connecting the ESP32 to a Wi-Fi network

◆ **DHT.h** - Reading DHT22 sensor data

◆ **Adafruit_Sensor.h** - Sensor support library

◆ **EEPROM.h** - Saving configuration settings in flash-backed storage

◆ **C++** - Programming language

## 🔨 How I Developed the Project

### Step 1 : Studied the Project Requirements

I studied the ESP32 multisensor concept and identified the required sensors, output devices, and control functions. The goal was to combine environmental monitoring with automatic and manual output control.

### Step 2 : Selected the Hardware Components

I identified the ESP32 as the main controller and selected the DHT22, PIR sensor, LDR, RGB LED, and relay/output circuit for their respective functions.

### Step 3 : Configured the Arduino IDE

I prepared the Arduino development environment, included the required libraries, and defined the GPIO pin assignments for the sensors and output devices.

### Step 4 : Implemented Sensor and Output Control

I structured the firmware to initialize the DHT22, read motion input, monitor analog light readings, and control the output and RGB LED according to the selected operating mode.

### Step 5 : Developed the Wi-Fi Web Server

I used the ESP32 Wi-Fi library and web-server functionality to create a browser-accessible interface. The interface provides mode selection, output controls, timer settings, light-threshold settings, and on-demand temperature and humidity readings.

### Step 6 : Implemented Four Operating Modes

➤ **Manual Mode:** The user controls the output through the web interface.

➤ **Auto PIR Mode:** Motion detection activates the output, with a configurable timer.

➤ **Auto LDR Mode:** The output responds to the configured light threshold.

➤ **Auto PIR and LDR Mode:** Motion and light conditions are combined to control the output.

### Step 7 : Added Persistent Settings

I used EEPROM functions to save the output state, selected mode, timer value, and LDR threshold. This allows the firmware to restore saved configuration values after restarting, subject to correct initialization and valid stored data.

### Step 8 : Prepared the System for Operation

The firmware connects to the configured Wi-Fi network, prints the assigned IP address to the Serial Monitor, and starts the web server. The browser interface can then be accessed from a device on the same network.

> **Development Note:** These steps describe the implementation represented in the source code. Hardware assembly and successful testing should only be claimed after they have actually been completed.

## ⚙️ How the System Works

① The ESP32 initializes the sensors, GPIO pins, and saved configuration.

② It connects to Wi-Fi and starts the web server.

③ The user selects an operating mode or adjusts the available settings in the browser.

④ The ESP32 evaluates motion and light conditions according to the selected mode.

⑤ The output and RGB LED respond to the programmed control logic.

⑥ Temperature and humidity readings can be requested through the web interface.

## 🚀 How to Set Up the Project

① Install the Arduino IDE and configure ESP32 board support.

② Install the required sensor libraries.

③ Open `ESP32_WiFi_Multisensor.ino`.

④ Replace the Wi-Fi placeholders with your own network credentials.

⑤ Check that the pin assignments match your circuit.

⑥ Select the appropriate ESP32 board and port.

⑦ Verify the code and upload it to the ESP32.

⑧ Open the Serial Monitor at **115200 baud**.

⑨ After Wi-Fi connects, copy the displayed IP address into a browser on the same network.

## 🎯 What I Learned

▸ ESP32 programming with Arduino IDE

▸ Sensor interfacing and GPIO configuration

▸ Wi-Fi communication and web-server development

▸ Manual and sensor-based automation

▸ Interrupt-based motion detection

▸ Persistent configuration storage

▸ Basic embedded-system control logic

## 📚 Reference

This learning project is based on the multisensor project presented in *Learn ESP32 with Arduino IDE* by Rui Santos and Sara Santos.

The original ebook is not included in this repository.

---

<p align="center">
  <b>🌱 Learning • Building • Innovating with IoT</b>
</p>

<p align="center">
  <i>Exploring embedded systems through hands-on project development.</i>
</p>

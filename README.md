# Ambulance Alarm Clock

An alarm clock designed to make sure you get out of bed. When the alarm goes off, the device activates multiple outputs including sound, lights, and motion, forcing the user to get out of bed and stop it manually.

## Features
* Configurable alarm time using two physical buttons
* 12-hour and 24-hour time format support
* Alarm enable/disable functionality
* Multi-modal alarm system (buzzer, LEDs, DC motor) 
* LCD display for time and alarm status
* Scrolling text display during alarm
* Night mode with reduced display brightness
* Alarm can only be stopped by pressing both buttons

## Hardware Requirements
- **Microcontroller:** Raspberry Pi Pico
- **Display:** 16x2 LCD (I2C interface)
- **Buttons:** 2x Momentary push buttons
- **Sound:** Active Buzzer
- **Lights:** 2x LEDs (used for alternating emergency lights)
- **Movement:** DC Motor for the movement

## Libraries Used

To compile this project, the following libraries are required:

* **[TimeLib](https://github.com/PaulStoffregen/Time)** – Manages the internal clock and timekeeping.
* **[DFRobot RGB LCD1602](https://github.com/DFRobot/DFRobot_RGBLCD)** – Controls LCD display

## Pin Mapping
| Component | Pin |
| :--- | :--- |
| Hour Button | 16 |
| Minute Button | 17 |
| Buzzer | 21 |
| LED 1 | 19 |
| LED 2 | 20 |
| Motor | 0 |

## System Overview

The system is built around a continuous loop that handles three main responsibilities:

- Reading and processing button inputs  
- Checking current time against the alarm time  
- Updating outputs (LCD, LEDs, buzzer, motor) based on system state  

The alarm behavior is implemented as a state-driven system where different outputs are activated depending on whether the system is in normal mode or alarm mode.

## Setup
1. Connect the hardware according to the pin mapping.
2. Install the required libraries.
3. Adjust the `setTime()` function in the `setup()` to your current time before uploading, or implement a real-time setting feature.
4. Upload the program to the microcontroller and wake up on time!

## Demo
(images/video) Will be added here

## Challenges
* Managing multiple button functions with only two inputs required implementing reliable short/long press detection using timing logic.
* Coordinating alarm behaviors (LEDs, buzzer, motor, display) without blocking execution required use of non-blocking timing with `millis()`.
* Limited 16x2 LCD space required a custom substring-based scrolling system for longer messages.
* Multiple system states (normal, alarm, setup) needed clear state management to avoid conflicting behavior.


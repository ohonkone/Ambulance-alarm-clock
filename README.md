# Ambulance Alarm Clock

An alarm clock designed to make sure you get out of bed. When the alarm goes off, the device activates multiple outputs including sound, lights, and motion, forcing the user to get out of bed and stop it manually.

<img width="1536" height="2048" alt="20260504_085054000_iOS 1 1" src="https://github.com/user-attachments/assets/2660fa06-c04b-4575-9dc5-32e3da8360ce" />


## Features
* Configurable alarm time using two physical buttons
* 12-hour and 24-hour time format support
* Alarm enable/disable functionality
* Multi-modal alarm system (buzzer, LEDs, DC motor) 
* LCD display for time and alarm status
* Scrolling text display during alarm
* Alarm can only be stopped by pressing both buttons

## Libraries Used

To compile this project, the following libraries are required:

* **[TimeLib](https://github.com/PaulStoffregen/Time)** – Manages the internal clock and timekeeping.
* **[DFRobot RGB LCD1602](https://github.com/DFRobot/DFRobot_RGBLCD)** – Controls LCD display

## Pin Mapping
| Component | Pin |
| :--- | :--- |
| Hour Button | 17 |
| Minute Button | 16 |
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
<img width="1536" height="2048" alt="20260504_085055000_iOS" src="https://github.com/user-attachments/assets/483b6f92-bc1b-486f-ac1d-c500372fb607" />
<img width="1536" height="2048" alt="20260504_085054000_iOS 2 1" src="https://github.com/user-attachments/assets/ff2e2c02-570f-4c61-90af-b4cb2ce94b0e" />
<img width="1536" height="2048" alt="20260504_085054000_iOS 1" src="https://github.com/user-attachments/assets/9247e4a4-4886-445f-9f87-0b39984f1721" />
<img width="1536" height="2048" alt="20260504_085054000_iOS 1" src="https://github.com/user-attachments/assets/65634acb-258d-4b4f-a064-83b7365fb901" />

(images/video) Will be added here

## Challenges
* Managing multiple button functions with only two inputs required implementing reliable short/long press detection using timing logic.
* Coordinating alarm behaviors (LEDs, buzzer, motor, display) without blocking execution required use of non-blocking timing with `millis()`.
* Limited 16x2 LCD space required a custom substring-based scrolling system for longer messages.
* Multiple system states (normal, alarm, setup) needed clear state management to avoid conflicting behavior.


--------------------------------------------------------------------------------------------


## **Electronics**

## Components

* Raspberry Pi Pico	1	
* USB Cable		1
* Breadboard big		1
* Jumpers cable	M-M / F-M	
* LEDs	Transparent/Red/Green	2/2/2
* Resistors	10K / 230	1/4
* Brushed DC Motor	GEARMOTOR 200 RPM 3-6V DC or STANDARD MOTOR 9100 RPM 6V	1
* Power MOSFET	IRLZ34N	1
* Diode	1N4007	1
* Magnetic Buzzer	AUDIO MAGNETIC XDCR 3-8V TH	1
* Battery holder	3/4 AAA batteries	1 -> 4.5V to circuit
* Buttons 2
* 16x2 LCD (I2C interface)

## Wiring

- **Note how to wire MOSFET, dc motor + diode, where to connect all components (GP pins), leds need resistors**
  
- Electronic components run on batteries
  
- Assembly and wiring in Tinkercad (note that Tinkercad don't have Raspberry Pi Pico, so it's placed in breadboard shown in the picture):
  https://www.tinkercad.com/things/dCtiujmw0vD-electronic-circuit-of-ambulance-alarm-clock?sharecode=n8KRjthndARLnjodSLvgcyvVyKkI40XEgiVX9qKJV4Q
  
- example picture of circuit:
<img width="906" height="781" alt="image" src="https://github.com/user-attachments/assets/9b2ca729-7b8a-4b81-9c37-87ad7aeab770" />

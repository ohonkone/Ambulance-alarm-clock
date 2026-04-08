# 🚑 Ambulance Alarm Clock

An alarm clock designed to make sure you get out of bed. When the alarm goes off, the ambulance flashes its lights, sounds a siren, and **physically drives away** so you have to catch it to turn it off.

## How it Works
1. Set the alarm time with the buttons on the ambulance.
2. When the time matches the alarm time, the DC motor activates, driving the ambulance forward.
3. LEDs start to flash in an alternating "emergency" pattern.
4. The buzzer plays a pulsing siren sound, that wakes you up.
5. To stop the alarm, you must catch the ambulance and press both buttons at the same time.

## Hardware Requirements
- **Microcontroller:** Raspberry Pi Pico
- **Display:** 16x2 LCD Screen 
- **Movement:** DC Motor (connected via `motorPin 0`)
- **Sound:** Active Buzzer
- **Lights:** 2x LEDs (Red/Blue)
- **Interaction:** 2x Momentary Push Buttons

## Libraries Used
To compile this project, you will need to install the following libraries in your Arduino IDE:
* [TimeLib.h](https://github.com/PaulStoffregen/Time) - Used for managing internal clock time.
* [LiquidCrystal.h](https://www.arduino.cc/reference/en/libraries/liquidcrystal/) - Used for the LCD interface.

## Pin Mapping
Coming soon.

## Setup
1. Connect the hardware according to the pin mapping.
2. Install the required libraries.
3. Adjust the `setTime()` function in the `setup()` to your current time before uploading, or implement a real-time setting feature.
4. Upload the code and wake up on time!

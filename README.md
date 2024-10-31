# Arduino-based Home Automation System with LED Strip Control

This project implements a small-scale home automation system using Arduino. The system integrates a DHT temperature sensor and an LED strip (using NeoPixel technology) to control the LED colors and brightness smoothly based on temperature thresholds. 

## Features
- Monitors ambient temperature using a DHT22 sensor.
- Controls an LED strip color and brightness based on temperature ranges:
  - Blue for cool temperatures (< 20°C)
  - Green for warm temperatures (20°C to 25°C)
  - Red for hot temperatures (> 25°C)
- Smooth transitions between colors for a visually appealing effect.

## Components Required
- Arduino board (e.g., Arduino Uno)
- DHT22 Temperature and Humidity Sensor
- NeoPixel LED Strip (30 LEDs or more)
- 220-ohm resistor (for the LED data pin)
- Breadboard and jumper wires
- Power supply for the LED strip (if needed)

## Libraries Required
To run this project, you need to install the following libraries in your Arduino IDE:
1. **DHT sensor library** by Adafruit:
   - Install from Library Manager in the Arduino IDE: `Sketch` -> `Include Library` -> `Manage Libraries...` and search for "DHT sensor library".
   
2. **Adafruit NeoPixel library**:
   - Install from Library Manager in the Arduino IDE: `Sketch` -> `Include Library` -> `Manage Libraries...` and search for "Adafruit NeoPixel".

## Installation
1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/JaredSantiago-code/LED-Home-Automation-System.git
2. Open the project in the Arduino IDE.
3. Install the required libraries.
4. Connect the DHT22 sensor and NeoPixel LED strip to the appropriate pins on the Arduino as defined in the code.
5. Upload the code to your Arduino board.

## Usage
- The system reads the ambient temperature every 2 seconds
- The LED strip will change its color based on the current temperature.
- Colors will transition smoothly

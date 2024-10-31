// Arduino-based Home Automation System with LED Strip Control
// Uses temperature sensor to control LED strip color and brightness smoothly based on temperature thresholds

#include <DHT.h>           // DHT library for temperature sensor
#include <Adafruit_NeoPixel.h>  // NeoPixel library for LED strip control

// Define sensor and LED strip pins
#define DHTPIN 2           // Temperature sensor connected to pin 2
#define LED_STRIP_PIN 6    // LED strip connected to pin 6
#define NUM_LEDS 30        // Number of LEDs in strip

// Set up the temperature sensor and LED strip
DHT dht(DHTPIN, DHT22);
Adafruit_NeoPixel strip(NUM_LEDS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

// Define temperature thresholds and LED colors
const float COOL_TEMP = 20.0;      // Cool temperature threshold
const float WARM_TEMP = 25.0;      // Warm temperature threshold
const float HOT_TEMP = 30.0;       // Hot temperature threshold

// Define colors for different temperature ranges
uint32_t coolColor = strip.Color(0, 0, 255);    // Blue for cool temps
uint32_t warmColor = strip.Color(0, 255, 0);    // Green for moderate temps
uint32_t hotColor = strip.Color(255, 0, 0);     // Red for hot temps

void setup() {
  Serial.begin(9600);
  dht.begin();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.println("System initialized. Monitoring temperature...");
}

void loop() {
  // Read temperature in Celsius every 2 seconds
  delay(2000);
  float temp = dht.readTemperature();
  
  // Check if reading is valid
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println("°C");

  // Determine color based on temperature
  uint32_t targetColor;
  if (temp < COOL_TEMP) {
    targetColor = coolColor;
  } else if (temp >= COOL_TEMP && temp < WARM_TEMP) {
    targetColor = warmColor;
  } else {
    targetColor = hotColor;
  }

  // Apply smooth transition to target color
  smoothTransitionToColor(targetColor, 50);  // Adjust transition speed as needed
}

// Function to smoothly transition the LED strip to the target color
void smoothTransitionToColor(uint32_t targetColor, uint8_t stepDelay) {
  for (int j = 0; j < NUM_LEDS; j++) {
    uint32_t currentColor = strip.getPixelColor(j);
    uint8_t currentRed = (currentColor >> 16) & 0xFF;
    uint8_t currentGreen = (currentColor >> 8) & 0xFF;
    uint8_t currentBlue = currentColor & 0xFF;
    
    uint8_t targetRed = (targetColor >> 16) & 0xFF;
    uint8_t targetGreen = (targetColor >> 8) & 0xFF;
    uint8_t targetBlue = targetColor & 0xFF;

    uint8_t newRed = currentRed + (targetRed - currentRed) * stepDelay / 255;
    uint8_t newGreen = currentGreen + (targetGreen - currentGreen) * stepDelay / 255;
    uint8_t newBlue = currentBlue + (targetBlue - currentBlue) * stepDelay / 255;

    strip.setPixelColor(j, strip.Color(newRed, newGreen, newBlue));
  }
  strip.show();
  delay(stepDelay);
}

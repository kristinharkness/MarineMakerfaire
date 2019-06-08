// Based on the example testing sketch for various DHT humidity/temperature sensors written by ladyada, public domain
// Modified for the Marine Makerfaire

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// Pins 7 and 8 will control the LEDs
#define RED_LED 7
#define BLUE_LED 8

// Define LED temperature and humidity thresholds
#define MAX_HUMIDITY 90
#define MAX_TEMPERATURE 100

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is, in this case 2
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Connect pin 7 to the positive leg of the Red LED
// Connect pin 8 to the positive leg of the Blue LED
// Connect each negative LED leg to ground using a 220 ohm resistor

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the output
  Serial.begin(9600);

  // Initialize the sensor
  dht.begin();

  // Initialize the LED pins for output and be sure they are off
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(h);
  Serial.print(" ");
  Serial.println(f);

  // If the humidity exceeds the threshold, turn on the blue LED
  // Otherwise, turn it off
  if (h > MAX_HUMIDITY) {
    digitalWrite(BLUE_LED, HIGH);
  } else {
    digitalWrite(BLUE_LED, LOW);
  }

  // If the temperature exceeds the threshold, turn on the red LED
  // Otherwise, turn it off
  if (f > MAX_TEMPERATURE) {
    digitalWrite(RED_LED, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
  }

  // Wait a few seconds between measurements
  delay(200);
}

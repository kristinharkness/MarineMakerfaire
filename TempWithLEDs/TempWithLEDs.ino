/********************************************************************/
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
/********************************************************************/
// Data wire for temperture sensor is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
/********************************************************************/
// Setup a oneWire instance to communicate with the temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
/********************************************************************/
// Pins 7 and 8 will control the LEDs
#define RED_LED 7
#define GREEN_LED 8
/********************************************************************/
// Define LED temperature thresholds
#define GREEN_TEMP 80
#define RED_TEMP 85

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.print("The green LED will light when temp > ");
  Serial.println(GREEN_TEMP);
  Serial.print("The red LED will light when temp > ");
  Serial.println(RED_TEMP);
  Serial.println("");

  // Start up the library
  sensors.begin();

  // Initialize the LED pins and be sure they are off
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  /********************************************************************/
  sensors.requestTemperatures(); // Send the command to get temperature readings
  /********************************************************************/
  float temp = sensors.getTempFByIndex(0); // Why "byIndex"?
  // You can have more than one DS18B20 on the same bus.
  // 0 refers to the first IC on the wire

  Serial.println(temp);

  if (temp > GREEN_TEMP) {
    digitalWrite(GREEN_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, LOW);
  }

  if (temp > RED_TEMP) {
    digitalWrite(RED_LED, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
  }

  delay(100);
}

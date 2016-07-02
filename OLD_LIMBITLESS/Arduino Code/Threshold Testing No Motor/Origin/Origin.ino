/*
 * limbitless EDITED
 *
 * Title: Limbitless v3
 * Author: Tyler Petresky <tylerpetresky.com>, Ambrose Douglas
 * Date: 7-14, 2-13-2016
 *
 * Desc: Basic code to allow the actuation a servo (closing of
 *       a prosthetic hand) based on bicep movement.
 *       The hand should open and close using a toggle 
 *       method.
 */

// Library for servo use
#include <Servo.h>

// Analog pin for the muscle sensor
int muscle_pin = A0;

int light_pin = 13;

// Threshold value that allows the hand to open and close.
// The scaled value of the muscle sensor's value is compared
// to this threshold value.
// Sample 6-year old was 20.0, Adult was 100.0
float toggle_threshold = 50.0;


// Sets up the system. Runs once on startup.
void setup()
{
  // Uncomment this for calibration purposes.
  Serial.begin(9600);
  
  pinMode(muscle_pin, INPUT);
  pinMode(light_pin, OUTPUT);
  
  
}

void loop()
{
  // Raw value of the muscle sensor reading
  float muscle_sensor_value = analogRead(muscle_pin),
  // Muscle sensor value scaled down just for easier working
  muscle_sensor_scaled = muscle_sensor_value * (180.0 / 1023.0);
  
  Serial.println(muscle_sensor_value);  
  
}

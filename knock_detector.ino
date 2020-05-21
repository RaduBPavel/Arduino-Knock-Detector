#include "tones.h"

// Constants
const int sensorPin = A0;
const int buzzerPin = 11;
const int threshold = 40;
const int buttonPin = 2;

// Variables
int sensorReading = 0;
int buttonState = HIGH;
int lastButtonState = HIGH;

// Data used for the melody
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the sensor data, and activate the buzzer if it crosses the threshold
  sensorReading = analogRead(sensorPin);
  Serial.println(sensorReading);
  if (sensorReading > threshold) {
    delay(1000);
    do {
      // Play the melody
      for (int thisNote = 0; thisNote < 8 && lastButtonState != LOW; thisNote++) {
        // Continue to read the input to reduce inaccuracies
        analogRead(sensorPin);
        
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(buzzerPin, melody[thisNote], noteDuration);

        int pauseDuration = noteDuration * 1.30;
        delay(pauseDuration);
        noTone(buzzerPin);

        // Verify if the button is pushed
        buttonState = digitalRead(buttonPin);
        if (buttonState == LOW) {
          lastButtonState = LOW;
        }
      }
    } while (lastButtonState != LOW);
  }

  // Reset button state
  lastButtonState = HIGH;
}

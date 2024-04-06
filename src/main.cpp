#include <Arduino.h>

// Pin Definitions
const int singleNoteBtnPin = A1;  // Pin connected to the button
const int doremiBtnPin = A2;  // Pin connected to the button
const int marioBtnPin = A3;  // Pin connected to the button
const int buzzerPin = 3;  // Pin connected to the buzzer

const int ledsPins[] = {10, 11, 12, 13};
const size_t ledsCount = 4;

// Define the frequencies for the musical scale (C major scale)
const float frequencies[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};


// Define the frequencies for the Mario Bros theme melody
const float mario[] = {
  659.25, 659.25, 0, 659.25, 0, 523.25, 659.25, 0, 783.99, 0, 392.00, 587.33, 0,
  783.99, 0, 987.77, 0, 0, 783.99, 0, 987.77, 0, 1174.66, 0, 0, 0, 0, 0, 0,
  659.25, 0, 0, 659.25, 0, 0, 659.25, 0, 0, 523.25, 0, 0, 659.25, 0, 0, 783.99,
  0, 0, 392.00, 0, 0, 587.33, 0, 0, 783.99, 0, 0, 987.77, 0, 0, 0, 0, 0, 783.99,
  0, 0, 987.77, 0, 0, 1174.66, 0, 0, 0, 0, 0
};

// Define the duration of each note
const int marioNoteDurations[] = {
  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125, 125, 125
};

void control_all_leds(int level)
{
  for (size_t i = 0; i < ledsCount; i++)
  {
    digitalWrite(ledsPins[i], level);
  }
}

void playNote(float freq, int duration = 0UL)
{
  control_all_leds(LOW);
  tone(buzzerPin, freq);  // Play each note of the scale
  delay(duration);        // Add a short delay between notes
  noTone(buzzerPin);      // Stop playing the note
  control_all_leds(HIGH);
}

void setup() {
  for (size_t i = 0; i < ledsCount; i++)
  {
    pinMode(ledsPins[i], OUTPUT);
  }

  // Initialize the button pin as input
  pinMode(singleNoteBtnPin, INPUT);
  pinMode(doremiBtnPin, INPUT);
  pinMode(marioBtnPin, INPUT);
  // Initialize the buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
  control_all_leds(HIGH);
}

void loop() {

  // Check if the button is pressed
  if (digitalRead(singleNoteBtnPin) == LOW) {
    playNote(440.0F, 500);
  }

  if (digitalRead(doremiBtnPin) == LOW) {
    // Play the musical scale
    for (int i = 0; i < 8; i++) {
      playNote(frequencies[i], 500);
    }
  }

  if (digitalRead(marioBtnPin) == LOW)
  {
    // Play the Mario Bros theme melody
    for (int i = 0; i < sizeof(mario) / sizeof(mario[0]); i++) 
    {
      playNote(mario[i], marioNoteDurations[i]);
    }
  }
}

#include <Arduino.h>

// Pin Definitions
const int singleNoteBtnPin = A1;  // Pin connected to the button
const int doremiBtnPin = A2;  // Pin connected to the button
const int marioBtnPin = A3;  // Pin connected to the button
const int buzzerPin = 3;  // Pin connected to the buzzer

const int ledsPins[] = {10, 11, 12, 13};
const size_t ledsCount = 4;

// Define the pins connected to the shift registers
const int DATA_PIN  = 8; // Pin connected to the serial data input (DS) of the shift registers
const int CLOCK_PIN = 7; // Pin connected to the shift register clock input (SH_CP)
const int LATCH_PIN = 4; // Pin connected to the shift register latch input (ST_CP)

const byte segments[] = {B00000001, B00000010, B00000100, B00001000}; 

// Define the digit patterns for 0-9 on a 7-segment display
const byte digitPatterns[] = {
    B00010000, // 0
    B11111001, // 1
    B10100100, // 2
    B10110000, // 3
    B10011001, // 4
    B10010010, // 5
    B10000010, // 6
    B11111000, // 7
    B10000000, // 8
    B10011000, // 9
    B11111111  // none
};

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

// Function to shift out data to the shift registers
void shiftOutData(byte data1, byte data2) {
    digitalWrite(LATCH_PIN, LOW); // Pull latch pin LOW to start data transmission
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data1); // Shift out the first data byte
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data2); // Shift out the second data byte
    digitalWrite(LATCH_PIN, HIGH); // Pull latch pin HIGH to latch data into the shift registers
}

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
    // Set pin modes
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    digitalWrite(LATCH_PIN, HIGH);

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

void loop() 
{
  // Check if the button is pressed
  if (digitalRead(singleNoteBtnPin) == LOW) 
  {
    shiftOutData(digitPatterns[1], segments[0]);
	  playNote(440.0F, 500);
    shiftOutData(digitPatterns[10], segments[0]);
  }

  if (digitalRead(doremiBtnPin) == LOW) {
    shiftOutData(digitPatterns[2], segments[1]);
    // Play the musical scale
    for (int i = 0; i < 8; i++) {
      playNote(frequencies[i], 500);
    }
    shiftOutData(digitPatterns[10], segments[1]);
  }

  if (digitalRead(marioBtnPin) == LOW)
  {
    shiftOutData(digitPatterns[3], segments[2]);
    // Play the Mario Bros theme melody
    for (int i = 0; i < sizeof(mario) / sizeof(mario[0]); i++) 
    {
      playNote(mario[i], marioNoteDurations[i]);
    }
    shiftOutData(digitPatterns[10], segments[2]);
  }
}

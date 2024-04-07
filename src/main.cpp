#include <Arduino.h>
#include "pitches.h"

#define LAUNCHPAD_STOP 255

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

const int noteFrequencies[] = 
{
    0,   // Index 0 is reserved for formatting
    31, 33, 35, 37, 39, 41, 44, 46, 49, 52,
    55, 58, 62, 65, 69, 73, 78, 82, 87, 93,
    98, 104, 110, 117, 123, 131, 135, 139, 147, 152, 156, 161, 165,
    175, 180, 185, 191, 196, 202, 208, 214, 220, 227, 233, 239, 247, 254, 262, 270, 277, 283, 294,
    311, 324, 330, 339, 349, 361, 370, 381, 392, 407, 415, 429, 440, 454, 466, 481, 494, 510, 523,
    554, 571, 587, 607, 622, 641, 659, 675, 698, 721, 740, 761, 784, 800, 820, 831, 850, 865, 880, 899, 915, 932,
    988, 999, 1030, 1047, 1085, 1109, 1150, 1175, 1245, 1319, 1397, 1480, 1568, 1661,
    1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960,
    3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978,
    5274, 5588, 5919, 6271, 6644, 7040, 7458, 7902
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
  Serial.begin(9600);
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

void launchpad_start_note(float freq)
{
  control_all_leds(LOW);
  tone(buzzerPin, freq);  // Play each note of the scale
}

void launchpad_stop_note()
{
  noTone(buzzerPin);      // Stop playing the note
  control_all_leds(HIGH);
}

void loop() 
{
  if (Serial.available()) {
    byte freq[1];
    Serial.readBytes(freq, 1);

    if (freq[0] == LAUNCHPAD_STOP)
    {
      shiftOutData(digitPatterns[10], segments[3]);
      launchpad_stop_note();
    }
    else 
    {
      shiftOutData(digitPatterns[4], segments[3]);
      launchpad_start_note(noteFrequencies[freq[0]]);
    }
  }
  // Check if the button is pressed
  if (digitalRead(singleNoteBtnPin) == LOW) 
  {
    shiftOutData(digitPatterns[1], segments[0]);
	  playNote(NOTE_A4, 500);
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
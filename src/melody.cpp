// #include <Arduino.h>

// // Define the pin number for the buzzer
// const int buzzerPin = 3;

// // Define the notes frequencies
// #define NOTE_C4  261.63
// #define NOTE_D4  293.66
// #define NOTE_E4  329.63
// #define NOTE_F4  349.23
// #define NOTE_G4  392.00
// #define NOTE_A4  440.00

// // Define the duration of each note
// int noteDurations[] = {
//   4, 4, 4, 4, 4, 4, 2,
//   4, 4, 4, 4, 4, 4, 2
// };

// void setup() {
//   // Set the buzzer pin as an output
//   pinMode(buzzerPin, OUTPUT);
// }

// void loop() {
//   // Define the melody
//   float melody[] = {
//     NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
//     NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
//   };

//   // Iterate over the melody and play each note
//   for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
//     int noteDuration = 1000 / noteDurations[i];
//     tone(buzzerPin, melody[i], noteDuration);
//     int pauseBetweenNotes = noteDuration * 1.30;
//     delay(pauseBetweenNotes);
//     noTone(buzzerPin);
//   }
//   // Pause between each repetition of the melody
//   delay(1000);
// }

#pragma once

void playWinSound(int speakerPin) {
  int melody[] = {659, 659, 880, 659, 523, 587, 494, 523};
  int noteDuration = 200;
  
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    tone(speakerPin, melody[i], noteDuration);
    delay(noteDuration + 50);  // Add a small delay between each note
  }
  
  noTone(speakerPin);  // Stop playing the melody
}

void playLostSound(int speakerPin)
{
  int melody[] = {131, 117, 104, 98, 87, 78, 69};
  int noteDuration = 200;
  
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    tone(speakerPin, melody[i], noteDuration);
    delay(noteDuration + 50);  // Add a small delay between each note
  }
  
  noTone(speakerPin);  // Stop playing the melody
}

void playFailSound(int speakerPin) {
   // Define the frequencies for the "fail" sound
  int frequencies[] = { 440, 392, 349, 293, 261 };

  // Play the frequencies in sequence
  for (int i = 0; i < 5; i++) {
    tone(speakerPin, frequencies[i], 200);
    delay(200);
  }

  noTone(speakerPin);  // Stop playing the sound
}
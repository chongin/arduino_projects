#include "joystick.h"
#include "game.h"

JoyStick * current_joy_stick = NULL;
Game* game = NULL;

const int LED_PIN = 9;
const int BUTTON_PIN = 8;
const int buzzerPin = 7;
void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  current_joy_stick = new JoyStick();
  game = new Game();
  game->Start();
}

void loop() 
{
  current_joy_stick->UpdateCommand();
  if (current_joy_stick->CurrentCommand() != CommandEnum::None)
  {
    Serial.println("Detect Operation:" + current_joy_stick->GetCommandStr());
    game->HandleCommand(current_joy_stick->CurrentCommand());
  }
  
  CheckGameResult();

  game->Update();

  delay(600);
}

void CheckGameResult()
{
  int val = digitalRead(BUTTON_PIN);
  if (val == HIGH)
  {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
    game->CalculateResult();
    WinHandling();
  }
}

void WinHandling()
{
  if (game->IsWin()) {
    playWinSound(buzzerPin);
    Serial.println("Win");
  } else if (game->IsLost()) {
    playLostSound(buzzerPin);
    Serial.println("Lost");
  } else if (game->IsFail()) {
    playFailSound(buzzerPin);
    Serial.println("Fail");
  }
}

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
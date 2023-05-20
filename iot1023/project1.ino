#include <IRremote.h>
#include <Servo.h>

const int LIGHT_BLOCKING_PIN = A3;
const int BUZZER_PIN = 9;
const int RECEIVER_PIN = 8;
const int SERVO_PIN = A5;
const int RED_PIN = A0;
const int GREEN_PIN = A1;
const int BLUE_PIN = A2;

IRrecv IR(RECEIVER_PIN);
Servo myservo;


void setup() {
  pinMode(LIGHT_BLOCKING_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  myservo.attach(SERVO_PIN);
  IR.enableIRIn();

  Serial.begin(9600);
}

void loop() {
  if (IR.decode()) {
    switch(IR.decodedIRData.decodedRawData)
    {
      case 0xF708FF00:
      {
        moveServoMotor(90);
        break;
      }
      case 0xA55AFF00: {
        moveServoMotor(0);
        break;
      } 
      case 0xBA45FF00: {
        redLightOn();
        break;
      }
      case 0xB946FF00: {
        greenLightOn();
        break;
      }
      case 0xB847FF00: {
        blueLightOn();
        break;
      }
      case 0xBB44FF00: {
        offAllLight();
        break;
      }
      default: {
        //Serial.println(IR.decodedIRData.decodedRawData, HEX);
        break;
      }
    }
    
    delay(200);
    IR.resume();
  }
  
  int val = analogRead(LIGHT_BLOCKING_PIN);
  if (val > 400) {
    buzzerOn();
  }
  else {
    buzzerOff();
  }
  delay(200);
}

void buzzerOn()
{
  digitalWrite(BUZZER_PIN, HIGH);
  Serial.println("buzzer on");
}

void buzzerOff()
{
  digitalWrite(BUZZER_PIN, LOW);
 // Serial.println("buzzer off");
}

void redLightOn()
{
  analogWrite(A0, 255);
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  Serial.println("red light on");
}

void greenLightOn()
{
  analogWrite(A1, 255);
  analogWrite(A0, 0);
  analogWrite(A2, 0);
  Serial.println("green light on");
}

void blueLightOn()
{
  analogWrite(A2, 255);
  analogWrite(A0, 0);
  analogWrite(A1, 0);
  Serial.println("blue light on");
}

void offAllLight()
{
  analogWrite(A0, 0);
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  Serial.println("all lights off");
}

void moveServoMotor(int degree)
{
  myservo.write(degree);
  Serial.print("servo move ");
  Serial.print(degree);
  Serial.println(" degree");
}
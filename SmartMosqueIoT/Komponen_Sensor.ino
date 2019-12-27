#include <Servo.h>

Servo myservo;

int servo = 9;
int sensorIR = 6;
int sensorLDR = A0;
int ledPinLDR = 8;
int sensorPIR = 10;
int ledPinPIR = 7;
int sensorFlame = A1;
int buzzer = 5;
int pos = 90;

void setup() {
  Serial.begin(9600);

  myservo.attach(servo);

  pinMode(sensorIR, INPUT);
  pinMode(servo, OUTPUT);
  pinMode(sensorLDR, INPUT);
  pinMode(ledPinLDR, OUTPUT);
  pinMode(ledPinPIR, OUTPUT);
  pinMode(sensorPIR, INPUT);
  pinMode(sensorFlame, INPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() {
  int val = digitalRead(sensorIR);
  int valLDR = analogRead(sensorLDR);
  int valPIR = digitalRead(sensorPIR);
  int valFlame = analogRead(sensorFlame);

  Serial.println(valFlame);
//  Serial.println(val);
//  Serial.println(valLDR);
//  Serial.println(valPIR);

  if (valLDR <= 600) {
    digitalWrite(ledPinLDR, HIGH);
    delay(200);
  } else {
    digitalWrite(ledPinLDR, LOW);
  }

  if (valPIR == HIGH) {
    digitalWrite(ledPinPIR, LOW);
  } else {
    digitalWrite(ledPinPIR, HIGH);
  }

  if (valFlame <= 200) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(500);
  } else {
    digitalWrite(buzzer, LOW);
  }

  if (val == LOW) {
    for (pos; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(10);
    }
    delay(1000);
  }

  if (val == HIGH) {
    for (pos; pos <= 90; pos += 1) {
      myservo.write(pos);
      delay(10);
    }
    delay(1000);
  }
}

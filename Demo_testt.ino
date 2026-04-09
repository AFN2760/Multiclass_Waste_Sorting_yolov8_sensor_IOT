#include <Servo.h>

Servo servop;   // plastic
Servo servow;   // wet
Servo servom;   // metal

bool objectDetected = false;

void setup() {
  pinMode(8, INPUT_PULLUP);   // IR sensor
  pinMode(A1, INPUT);         // Rain sensor
  pinMode(A0, INPUT);         // Metal sensor

  servop.attach(11);
  servow.attach(10);
  servom.attach(9);

  servop.write(0);
  servow.write(0);
  servom.write(0);

  Serial.begin(9600);
}

void loop() {

  int IRval = digitalRead(8);

  if (IRval == 0 && !objectDetected) {   // object just arrived
    objectDetected = true;

    delay(1000); // small delay so object reaches sensors

    int Metalval = analogRead(A0);
    int Rainval  = analogRead(A1);

    if (Metalval <= 200) {
      Serial.println("Metal Object");
      servom.write(90);
      delay(1500);
      servom.write(0);
    }
    else if (Rainval <= 800) {
      Serial.println("Wet Object");
      servow.write(90);
      delay(1500);
      servow.write(0);
    }
    else {
      Serial.println("Plastic Object");
      servop.write(90);
      delay(1500);
      servop.write(0);
    }
  }

  if (IRval == 1) {   // object removed
    objectDetected = false;
    Serial.println("Nothing Detected");
  }

  delay(200);
}

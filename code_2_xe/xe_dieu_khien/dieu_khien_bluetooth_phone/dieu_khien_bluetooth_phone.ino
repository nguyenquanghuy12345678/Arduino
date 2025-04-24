// --- Robot Điều Khiển Bằng Bluetooth ---
// Arduino Uno R3, L298N, 4 motor, 4 servo SG90, Bluetooth (HC-05/HC-06)

#include <Servo.h>

// Servo SG90
Servo servoRotate, servoLiftL, servoLiftR, servoGrip;

// L298N motor control
const int ENA = 5, IN1 = 6, IN2 = 7;
const int ENB = 9, IN3 = 8, IN4 = 4;

char command;

void setup() {
  Serial.begin(9600); // HC-05 default: 9600

  // Servo setup
  servoRotate.attach(3);
  servoLiftL.attach(2);
  servoLiftR.attach(A0);
  servoGrip.attach(A1);

  // Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    Serial.println(command);  // Phản hồi về app nếu cần

    switch (command) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopMotors(); break;

      case 'X': servoRotate.write(90); break;
      case 'x': servoRotate.write(0); break;

      case 'U': servoLiftL.write(120); servoLiftR.write(120); break;
      case 'D': servoLiftL.write(80); servoLiftR.write(80); break;

      case 'O': servoGrip.write(60); break;
      case 'C': servoGrip.write(100); break;
    }
  }
}

// Motor functions
void moveForward() {
  analogWrite(ENA, 150); analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, 150); analogWrite(ENB, 150);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, 120); analogWrite(ENB, 120);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 120); analogWrite(ENB, 120);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// --- Robot Điều Khiển PS2 ---
// Arduino Uno R3, L298N, 4 motor, 4 servo SG90, PS2 Controller

#include <PS2X_lib.h>
#include <Servo.h>

// PS2 chân kết nối (tuỳ thư viện có thể cần đổi lại)
#define PS2_DAT 12
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 13

PS2X ps2x;

// Servo SG90
Servo servoRotate, servoLiftL, servoLiftR, servoGrip;

// L298N motor control
const int ENA = 5, IN1 = 6, IN2 = 7;
const int ENB = 9, IN3 = 8, IN4 = 4;

void setup() {
  Serial.begin(9600);

  // Khởi động PS2 Controller
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);

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
  ps2x.read_gamepad();

  // === Điều khiển di chuyển ===
  if (ps2x.Button(PSB_UP))       moveForward();
  else if (ps2x.Button(PSB_DOWN)) moveBackward();
  else if (ps2x.Button(PSB_LEFT)) turnLeft();
  else if (ps2x.Button(PSB_RIGHT)) turnRight();
  else stopMotors();

  // === Điều khiển tay robot ===
  if (ps2x.ButtonPressed(PSB_GREEN))  servoRotate.write(90);
  if (ps2x.ButtonPressed(PSB_BLUE))   servoRotate.write(0);

  if (ps2x.Button(PSB_L1))  servoLiftL.write(120);
  else                      servoLiftL.write(80);

  if (ps2x.Button(PSB_R1))  servoLiftR.write(120);
  else                      servoLiftR.write(80);

  if (ps2x.Button(PSB_CIRCLE)) servoGrip.write(60);
  else                         servoGrip.write(100);

  delay(50);
}

// Motor functions
void moveForward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

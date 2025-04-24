#include <Arduino.h>
#line 1 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
// Khai báo chân motor
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;
const int ENB = 10;
const int IN3 = 8;
const int IN4 = 9;

// 5 cảm biến line
const int lineSensor[5] = {A0, A1, A2, A3, A4};

// Cảm biến tường (LM393)
const int wallSensor = A5;

// Biến lưu giá trị cảm biến
int sensorValues[5];

#line 18 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void setup();
#line 38 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void loop();
#line 76 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void forward();
#line 83 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void curveLeft();
#line 90 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void curveRight();
#line 97 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void sharpLeft();
#line 104 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void sharpRight();
#line 111 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void crossIntersection();
#line 115 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void stopMotors();
#line 18 "D:\\Documents\\Vidieukhien\\code_2_xe\\xe_do_line\\xe_do_line.ino"
void setup() {
  // Motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Cảm biến line
  for (int i = 0; i < 5; i++) {
    pinMode(lineSensor[i], INPUT);
  }

  // Cảm biến tường
  pinMode(wallSensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Đọc cảm biến line
  for (int i = 0; i < 5; i++) {
    sensorValues[i] = digitalRead(lineSensor[i]);
  }

  // Ghép bit thành pattern
  int pattern = 0;
  for (int i = 0; i < 5; i++) {
    pattern |= (sensorValues[i] << (4 - i));
  }

  // Xử lý theo pattern
  switch (pattern) {
    case 0b00100: forward(); break;
    case 0b01100:
    case 0b01000: curveLeft(); break;
    case 0b11000:
    case 0b10000: sharpLeft(); break;
    case 0b00010:
    case 0b00110: curveRight(); break;
    case 0b00011:
    case 0b00001: sharpRight(); break;
    case 0b11111: crossIntersection(); break;
    default: stopMotors(); break;
  }

  // Xử lý khi gần tường
  int wall = digitalRead(wallSensor);
  if (wall == 0) {
    stopMotors(); // hoặc xử lý leo tường
  }

  delay(20); // delay nhỏ giúp ổn định
}

// Hàm điều khiển motor

void forward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void curveLeft() {
  analogWrite(ENA, 100);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void curveRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 100);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void sharpLeft() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void sharpRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 0);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void crossIntersection() {
  forward(); // Hoặc thêm chức năng lựa chọn rẽ tại đây
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}


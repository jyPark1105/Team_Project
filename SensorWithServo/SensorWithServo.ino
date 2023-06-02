#include <Servo.h>    // 서보모터 라이브러리

#define baudRate 9600
#define LM35 A0      // LM35 핀을 Analog 0번 핀으로
#define CDS A1       // CDS 핀을 Analog 1번 핀으로
#define SERVO 12      // SERVO 핀을 Digital 12번 핀으로

Servo servo;       // Servo의 인스턴스 생성

void setup() {
  Serial.begin(baudRate);    // 시리얼 모니터 통신 9600bps
  servo.attach(SERVO);  // 서보 모터 핀 설정
}

void loop() {
  int angle = 90; // 최초 : 90도
  for (angle = 0; angle <= 180; angle++) { // 0도에서 180도로 1도씩 이동
  servo.write(angle); 
  delay(1000);
  }
  for (angle = 180; angle >= 0; angle--) { // 180도에서 0도로 1도씩 이동
  servo.write(angle);
  delay(1000);
  }
  float Reading_Temp = analogRead(LM35);
  float TempC = (5.0*Reading_Temp*100.0)/1024.0;
  float Light_Lev = analogRead(CDS)/ 1023.0;   // 온도, 밝기를 float형으로 선언
  
  Serial.print("TempC : ");      // TempC 시리얼 모니터에 출력
  Serial.print(TempC);
  Serial.print("℃");             // \t : TempC출력과의 일정 간격 유지를 위한 개행문자, \n(줄 바꿈)과 다름
  Serial.print("\tLight level : ");
  Serial.print(Light_Lev);
  Serial.print("\n");


  if(TempC >= 45) { // LM35값 읽은 결과 25℃ 이상일 때 평균 TempC : 45℃
    for (angle = 0; angle <= 180; angle++) {
    servo.write(angle); 
    delay(500);
    }
    for (angle = 180; angle >= 0; angle--) {
    servo.write(angle);
    delay(500);
    }
  }
  else if(TempC < 45){
    for (angle = 0; angle <= 180; angle++) {
    servo.write(angle); 
    delay(2500);
    }
    for (angle = 180; angle >= 0; angle--) {
    servo.write(angle);
    delay(2500);
    }
  }
delay(2000); 
}

  
  
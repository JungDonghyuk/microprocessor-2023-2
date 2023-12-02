#include <SPI.h>

#define NUM_MOTORS 16

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  
  SPI.begin(); 
  pinMode(11, INPUT); // 1번 아두이노 수신 핀 설정
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
 
}

void loop() {
  uint8_t receivedValue = 0;
  
  if (digitalRead(11) == LOW) {
    receivedValue = SPI.transfer(0x00); // 마스터에서 전송된 값을 수신
    digitalWrite(11, HIGH); // 상태를 리셋하기 위해 핀을 HIGH로 설정
    Serial.println(receivedValue); // 수신된 값을 시리얼 모니터에 출력
  }

  DDRB |= 0xFF; // DDRB를 모두 출력으로 설정
  PORTB = receivedValue; // PORTB에 수신된 값을 할당

  delay(1000);
}

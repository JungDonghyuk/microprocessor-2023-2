#include <SPI.h>

#define NUM_MOTORS 16

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  
  SPI.begin(); 
  pinMode(13, OUTPUT); //1번 아두이노 송신 핀 설정
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
 
}

void loop() {
  uint16_t NUM_ON = 0; 
  DDRB = 0xFF;

  uint16_t POS_VAL = pow(2, NUM_MOTORS) - 1;
  uint16_t value = random(0, POS_VAL);

  for (uint8_t i = 0; i < 16; i++) {
    NUM_ON += (value >> (15 - i)) & 0x01;
  }

  if (NUM_ON > 10) {
    uint8_t lByte = (value >> 8);
    uint8_t hByte = (value & 0xff);
    Serial.println(lByte);

    
    digitalWrite(10, LOW); 
    SPI.transfer(lByte); 
    digitalWrite(10, HIGH); 

    
  

    delay(1000);
  }
}

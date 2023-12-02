#include <SPI.h>

#define NUM_MOTORS 16

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  
  SPI.begin(); 
  pinMode(SS_1, OUTPUT);
  pinMode(SS_2, OUTPUT); 
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

    
    digitalWrite(SS_1 LOW); 
    SPI.transfer(lByte); 
    digitalWrite(SS_1, HIGH); 

    
    digitalWrite(SS_2, LOW); 
    SPI.transfer(hByte); 
    digitalWrite(SS_2, HIGH); 

    delay(1000);
  }
}

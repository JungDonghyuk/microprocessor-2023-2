#define NUM_MOTORS 16

void setup() {
  Serial.begin(9600);
}
// 구현을 위해 loop함수 사용 
// 실제 코드에서는 loop빼고!!
void loop() {
  uint8_t NUM_ON = 0;  
  DDRB = 0xFF;  

  uint8_t POS_VAL = pow(2, NUM_MOTORS);
  uint8_t value = random(0, POS_VAL + 1);

  for (uint8_t i = 0; i < 8; i++) {
    NUM_ON += (value >> (7 - i)) & 0x01;
  }
  //수정 필요! 시리얼 모니터에서 아웃풋 항상 16자리가 아님.......
  //요것만 바꾸면 완성일듯..?
  if (NUM_ON > 10) {
    Serial.println(value);//실제 코드의 경우   PORB |= value
  }
  //   컨트롤러  2개 필요함 (모터 제어 핀 16개, 한 컨트롤러당 8개씩 제어)
  //  포인터 써서 16비트를 8비트 8비트로 각 컨트롤러에 
}

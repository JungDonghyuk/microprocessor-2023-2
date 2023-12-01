#define NUM_MOTORS 16

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
}
// 구현을 위해 loop함수 사용 
// 실제 코드에서는 loop빼고!!
void loop() {
  uint16_t NUM_ON = 0; 
  DDRB = 0xFF;

  uint16_t POS_VAL = pow(2, NUM_MOTORS) - 1;
  uint16_t value = random(0, POS_VAL);
//계속 출력값이 16비트가 아닌데 왜 아닐까........... 
?? *** 오류 수정해야함*****
  for (uint8_t i = 0; i < 16; i++) {
    NUM_ON += (value >> (15 - i)) & 0x01;
  }
  if(NUM_ON > 10){
    Serial.println(value);
  }
} 

  //   컨트롤러  2개 필요함 (모터 제어 핀 16개, 한 컨트롤러당 8개씩 제어)
  //  포인터 써서 16비트를 8비트 8비트로 각 컨트롤러에 

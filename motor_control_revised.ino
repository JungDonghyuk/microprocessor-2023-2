#define NUM_MOTORS 16

void setup() {
Serial.begin(9600);
}

void loop() {
uint16_t NUM_ON = 0; // NUM_ON 변수의 타입을 uint16_t로 변경
DDRB = 0xFF;

uint16_t POS_VAL = pow(2, NUM_MOTORS) - 1;
uint16_t value = random(0, POS_VAL);

for (uint8_t i = 0; i < 16; i++) {
NUM_ON += (value >> (15 - i)) & 0x01;
}

if (NUM_ON > 10) {
Serial.print(value, BIN); // 16진수로 출력하기 위해 Serial.print() 사용
Serial.println(); // 줄바꿈 추가
delay(1000);
}
}
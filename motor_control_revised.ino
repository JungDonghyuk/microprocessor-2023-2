#define NUM_MOTORS 16

void setup() {
Serial.begin(9600);
while (!Serial) {
; // 시리얼 포트가 연결될 때까지 기다립니다. 이 코드는 네이티브 USB에서 필요합니다.
}
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
for(int i=15; i>=0; i--) {
Serial.print((value >> i) & 0x1);
}
Serial.println(); // 줄바꿈 추가
delay(1000);
}
}

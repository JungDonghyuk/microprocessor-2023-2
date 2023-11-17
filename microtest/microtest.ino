
#define OC2A 0x08

uint8_t pwm_level = 0;

ISR(TIMER2_COMPA_vect){
  OCR2A = pwm_level;
}

void loop() {
  if (Serial.available()) {
    pwm_level = Serial.parseInt() ;
    Serial.println(pwm_level);
  }
}

void setup() {
  cli();
  
  DDRB |= OC2A;
  TCCR2A |= (1 << WGM21) | (1 << WGM20);


}
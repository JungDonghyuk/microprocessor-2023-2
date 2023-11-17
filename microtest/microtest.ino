
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
void Stepper::step(int steps_to_move)
{
  int steps_left = abs(steps_to_move); 
  
  if (steps_to_move > 0) { this->direction = 1; }
  if (steps_to_move < 0) { this->direction = 0; }
  
  while (steps_left > 0)
  {
    unsigned long now = micros();
    if (now - this->last_step_time >= this->step_delay)
    {
      this->last_step_time = now;
      
      if (this->direction == 1)
      {
        this->step_number++;
        if (this->step_number == this->number_of_steps) {
          this->step_number = 0;
        }
      }
      else
      {
        if (this->step_number == 0) {
          this->step_number = this->number_of_steps;
        }
          this->step_number--;
      }
      steps_left--;
      
      if (this->pin_count == 5){
        stepMotor(this->step_number % 10);
else
stepMotor (this->step_number % 4);
}

{
* Moves the motor forward or backwards.
void Stepper::stepMotor(int thisStep)
if (this->pin_count == 2) {
switch (thisStep) {
case 0: // 01
digitalWrite(motor_pin_1, LOW);
digitalWrite(motor_pin_2, HIGH);
break;
case 1: // 11
digitalWrite(motor_pin_1, HIGH);
digitalWrite(motor_pin_2, HIGH);
break;
case 2: // 10
digitalWrite(motor_pin_1, HIGH);
digitalWrite(motor_pin_2, LOW);
break;
case 3:
// 00
digitalWrite(motor_pin_1, LOW);
digitalWrite(motor_pin_2, LOW);
break;
｝
｝
if (this->pin_coun...

}

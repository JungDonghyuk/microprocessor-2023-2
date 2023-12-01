#define NUM_LEDS 4
#define ADC_RESOLUTION_IN_BIT 10

const uint16_t step = pow(2, ADC_RESOLUTION_IN_BIT) / NUM_LEDS;

void init_LED(){
   DDRB = 0X0F;
}

void init_Serial(){

  Serial.begin(9600);
  Serial.print("LED step: ");
  Serial.println(step);
  delay(1000);
}
void init_ADC(){

ADMUX |= (0<< REFS1) | (1<< REFS0);
ADMUX |= (0<< ADLAR);
ADMUX |= (0<<MUX3) | (0<<MUX2) | (0<<MUX1) |(0<<MUX0);
ADCSRA |= (1<<ADEN);
ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

}

void setup(){
  init_Serial();
  init_ADC();
  init_LED();
}

void loop(){
  ADCSRA |= (1 << ADSC);
  while(ADCSRA & (1<<ADSC));

  uint16_t value = ADC;

  uint8_t leds = 0x00;{
  for(uint8_t i = 0; i < NUM_LEDS; i++){
    if(value > step * i){
      leds |= (1 << i);
    }
  }

  PORTB = leds;
  Serial.println(value);
  delay(1);}
}
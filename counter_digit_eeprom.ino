#define SEGMENT_DELAY 2
#define NUM_DIGITS 4
#define NUM_SEGMENTS 8
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#define ADC_RESOLUTION_IN_BIT 10
const uint16_t step = pow(2, ADC_RESOLUTION_IN_BIT) / 4;

void init_Serial(){
  Serial.begin(9600);
  delay(1000);
}

void init_ADC(){
  ADMUX |= (0<< REFS1) | (1<< REFS0);
  ADMUX |= (0<< ADLAR);
  ADMUX |= (0<<MUX3) | (0<<MUX2) | (0<<MUX1) |(0<<MUX0);
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

uint16_t read_ADC(uint8_t channel) {
  ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  return ADC;
}

LiquidCrystal_I2C lcd(0x27,16,2);

const uint8_t patterns[] = {
  0xFC, // 0b 1111 1100 == a b c d e f g dp: 0
  0x60, // 0b 0110 0000: 1
  0xDA, // 0b 1101 1010: 2
  0xF2,
  0x66,
  0xB6,
  0XBE,
  0xE4,
  0xFE,
  0xE6,
};

uint8_t digit_select_pin[NUM_DIGITS] = {1,2,3,4};
uint8_t segment_pin[NUM_SEGMENTS] = {5, 6, 7, 8, 9, 10, 11, 12};

void setup(){
  for(uint8_t i = 0; i < NUM_DIGITS; i++){
    pinMode(digit_select_pin[i], OUTPUT);
  }
  for(uint8_t i = 0; i < NUM_SEGMENTS; i++){
    pinMode(segment_pin[i], OUTPUT);
  }
init_Serial();
init_ADC();  
}

void loop(){
  static uint16_t deci_sec = 0;
  static uint8_t sec = 0;
  static uint8_t min = 0;
  static uint16_t time_previous = 0;
  static uint8_t writeCount = 0;

  uint16_t potentiometer1 = read_ADC(0); //시작점의 조도센서 값이라고 가정함
  uint16_t potentiometer2 = read_ADC(1); //도착점의 조도센서 값이라고 가정함

  uint16_t time_current = millis();
  uint16_t NEW_RECORD = min*1000 + sec*10 + deci_sec;
  uint16_t OLD_RECORD;
  uint8_t address = 0;
  if(potentiometer1 >500){
    if(time_current - time_previous >= 100){
      deci_sec++;
      if(deci_sec == 10){
        deci_sec = 0;
        sec++;
        if(sec == 60){
          sec = 0;
          min++;
          }
      }
      time_previous = time_current;
    }
      else if(potentiometer2 > 500) {
        writeCount++;
        if(writeCount <= 10) {
          lcd.begin(16, 2); 
          lcd.init();
          lcd.backlight(); 
  
         EEPROM.get(address, OLD_RECORD);
          if(sec > 5) {
            if(OLD_RECORD != 0) {
              if(OLD_RECORD > NEW_RECORD) {
                EEPROM.put(address, NEW_RECORD);
                lcd.setCursor(6,0);  
                lcd.print("NEW SCORE");
                lcd.setCursor(6,1);  
                lcd.print(NEW_RECORD);
      
              }
              else if(OLD_RECORD == NEW_RECORD) {
                EEPROM.put(address, NEW_RECORD);
              }
              else if(OLD_RECORD <= NEW_RECORD) {
                lcd.setCursor(6,0);  
                lcd.print("FAIL");
              }
            } 
            else if(OLD_RECORD == 0) {
              EEPROM.put(address, NEW_RECORD);
              lcd.setCursor(6,0);  
              lcd.print("NEW SCORE");
              lcd.setCursor(6,1);  
              lcd.print(NEW_RECORD);  

            }
          }
          else if(sec <= 5){
          }
            
        }
        else {
          EEPROM.put(address, 0);
          writeCount = 0; 
        }
  
      return; // 게임이 종료되는 시점, 여기서 무조건 끝남
      }
    show_four_digits(min * 1000 + sec * 10 + deci_sec);
    }
  }
void show_digit(uint8_t pos, uint8_t number){
  for(int i = 0; i < 4; i++){
    if(i == pos){
      digitalWrite(digit_select_pin[i], LOW);
    }
    else {
      digitalWrite(digit_select_pin[i], HIGH);
    }
  }

  for(uint8_t i = 0; i < NUM_SEGMENTS; i++){
    bool on_off = bitRead(patterns[number], 7 - i);
    digitalWrite(segment_pin[i], on_off);
  }
  delay(SEGMENT_DELAY);
}

void show_four_digits(uint16_t number){
  uint8_t thousand = number / 1000;
  number = number % 1000;
  uint8_t hundred = number / 100;
  number = number % 100;
  uint8_t ten = number / 10;
  uint8_t one = number % 10;

  show_digit(0, thousand);
  show_digit(1, hundred);
  show_digit(2, ten);
  show_digit(3, one);
}
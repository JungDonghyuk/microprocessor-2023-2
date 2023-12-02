int value = 0;
#define SEGMENT_DELAY 2
#define NUM_DIGITS 4
#define NUM_SEGMENTS 8
#define SEGMENT_DELAY 2
int potentiometer =0;
#include <EEPROM.h>
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

const uint8_t digit_select_pin[NUM_DIGITS] = {
  5, 4, 3, 2};

const uint8_t segment_pin[NUM_SEGMENTS] = {
  6, 7, 8, 9, 10, 11, 12, 13};


void setup() {
  for(uint8_t i = 0; i < NUM_DIGITS; i++){
    pinMode(digit_select_pin[i], OUTPUT);
  }
  for(uint8_t i = 0; i < NUM_SEGMENTS; i++){
    pinMode(segment_pin[i], OUTPUT);
  }
}

void loop() {
  
   static uint8_t deci_sec = 0;
  static uint8_t min = 0;
  static uint8_t time_previous = 0;
  uint16_t counter = millis();
  uint16_t current_time = min*1000 + deci_sec;
 

  if(counter - time_previous >= 100){
   deci_sec++;
    if(deci_sec == 600){
      deci_sec = 0;
      min++;
      if(min == 5){
        value = 0;
      }
    }
  else if(potentiometer == 1){
    value = 0;
    EEPROM.put(0,current_time);
  }
  }
  show_four_digits (current_time);
}



void EEPROM_write(uint16_t uiAddress, uint8_t ucData) {

  EEAR = uiAddress;
  EEDR = ucData;
  EECR |= (1<<EEMPE);
  EECR |= (1<<EEPE);
}

void show_digit(uint8_t pos, current_time){
  for(int i = 0; i < 4; i++){
    if(i == pos){
      digitalWrite(digit_select_pin[i], LOW);
    }
    else {
      digitalWrite(digit_select_pin[i], HIGH);
    }
  }

  for(uint8_t i = 0; i < NUM_SEGMENTS; i++){
    bool on_off = bitRead(patterns[current_time], 7 - i);
    digitalWrite(segment_pin[i], on_off);
  }
}

void show_four_digits(current_time){
  current_time = current_time % 10000;
  uint8_t thousand = current_time / 1000;
  current_time = current_time % 1000;
  uint8_t hundred = current_time / 100;
  current_time = current_time % 100;
  uint8_t ten = current_time /10 ;
  uint8_t one = current_time %10 ;
  
  show_digit(0, thousand); 
  delay (SEGMENT_DELAY);
  
  show_digit (1, hundred); 
  delay (SEGMENT_DELAY) ;
  
  show_digit(2, ten); 
  delay (SEGMENT_DELAY) ;
  
  show_digit (3, one); 
  delay (SEGMENT_DELAY) ;
}

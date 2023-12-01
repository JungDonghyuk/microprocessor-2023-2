#define NUM_SEGMENTS 8 

const uint16_t number_to_show = 1357;

const_uint8_t patterns[] = {
  0xFC,
  0X60.
  0XDA,
  0XF2,
  0X66,
  0XB6,
  0XBE,
  0xE4,
  0XFE,
  0XE6,
}

const uint8_t digit_select_pin [NUM_DIGITS] = {5, 4, 3, 2};
const uint8_t segment_pin [NUM_SEGMENTS] = {6, 7, 8, 9, 10, 11, 12, 13};

void setup(){
  for(uint8_t i=0; i<NUM_SEGMENTS, i++){
    pinMode(digit_select)
  }
}
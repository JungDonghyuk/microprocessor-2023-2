void loop() {

  static uint8_t deci_sec = 0;
  static uint8_t min = 0;
  static time_previous = 0;
  uint16_t counter = millis();
  
  if(counter >= 100){
    deci_sec++;
    if(deci_sec == 600){
      deci_sec = 0;
      min++;
      if(min == 5){
        min = 0;
      }
    }
    time_previous = time_current;
  }
  LCD_ON(min*1000 + deci_sec);
}


// 병합시킬 코드에서 min 정의
if (min = 5) {
  println()
}
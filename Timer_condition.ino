void loop() {
//  [분, 10*초, 초, 10^-1초]
  static uint8_t deci_sec = 0;
  static uint8_t min = 0;
  static time_previous = 0;
  uint16_t counter = millis();
  
  if(counter - time_previous >= 100){
    deci_sec++;
    if(deci_sec == 600){
      deci_sec = 0;
      min++;
      if(min == 5){
        value = 0;//모든 모터 내리기
      }
    }
    time_previous = counter;
  }
  SEG_ON(min*1000 + deci_sec); //4 7 segment로 출력
}
//타이머 제한 5분으로 할 예정, 그 전에 완료했을 때 어떻게 타이머 중지시킬지 생각해보기....

// 5분이 되면 
if (min = 5) {
  ()
}
if (도착지점 조도센서 감지되면)
  //정지하고
  
// 

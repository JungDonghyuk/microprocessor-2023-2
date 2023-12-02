void setup() {
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t value1 = digitalRead(8);
  uint16_t value2 = digitalRead(9);
  uint16_t value3 = digitalRead(7);
  uint16_t value4 = digitalRead(6);

  if (value1!=0 & value2!=0 & value3!=0 & value4!=0 ){
    Serial.println("Normal");
     delay(100);

  }
  if((value1==0) && (value2!=0) && (value3!=0) && (value4!=0)){
    Serial.println("1");
    delay(150);
  }
  else if((value2==0) && (value1!=0) && (value3!=0) && (value4!=0)){
   Serial.println("2");
   delay(150);  
  }
  else if((value3==0) && (value2!=0) && (value1!=0) && (value4!=0)){
     Serial.println("3");
     delay(150);
  }
  else if((value4==0) && (value2!=0) && (value3!=0) && (value1!=0)){
     Serial.println("4");
     delay(150);
  }
  
}
#include <SPI.h>

#define NUM_MOTORS 16
#define SLAVE_SELECT_PIN 10

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  SPI.begin();
  pinMode(SLAVE_SELECT_PIN, OUTPUT); // Slave Select pin as output
  digitalWrite(SLAVE_SELECT_PIN, HIGH); // Start with Slave Select high (not selected)
}

void loop() {
  uint16_t value = random(0, pow(2, NUM_MOTORS) - 1); // 16-bit random number

  uint8_t lByte = (value >> 8); // high byte
  uint8_t hByte = value & 0xff; // low byte

  digitalWrite(SLAVE_SELECT_PIN, LOW); // Select the slave
  SPI.transfer(lByte); // Send high byte
  SPI.transfer(hByte); // Send low byte
  digitalWrite(SLAVE_SELECT_PIN, HIGH); // Deselect the slave

  delay(1000);
}
    delay(1000);
  }
}

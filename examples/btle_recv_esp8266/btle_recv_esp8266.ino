#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>

RF24 radio(5,SS);  //CE, CS

BTLE btle(&radio);

void setup() {

  Serial.begin(115200);

  Serial.println("BTLE advertisement receiver");

  btle.begin("");
}

void loop() {
  static uint8_t read_byte;

  if (btle.listen(200)) {
    Serial.println();Serial.print("MAC ");
    read_byte = btle.buffer.mac[5];if (read_byte < 0x10) Serial.print("0");Serial.print(read_byte,HEX);Serial.print(":");
    read_byte = btle.buffer.mac[4];if (read_byte < 0x10) Serial.print("0");Serial.print(read_byte,HEX);Serial.print(":");
    read_byte = btle.buffer.mac[3];if (read_byte < 0x10) Serial.print("0");Serial.print(read_byte,HEX);Serial.print(":");
    read_byte = btle.buffer.mac[2];if (read_byte < 0x10) Serial.print("0");Serial.print(read_byte,HEX);Serial.print(":");
    read_byte = btle.buffer.mac[1];if (read_byte < 0x10) Serial.print("0");Serial.print(read_byte,HEX);Serial.print(":");
    read_byte = btle.buffer.mac[0];if (read_byte < 0x10) Serial.print("0");Serial.print(read_byte,HEX);Serial.println();
    Serial.print("   [");
    for (uint8_t i = 0; i < (btle.buffer.pl_size)-6; i++) {
      read_byte = btle.buffer.payload[i];
      if (read_byte < 0x10) Serial.print("0");
      Serial.print(read_byte,HEX);
      Serial.print(" ");
    }
    Serial.println("]");
  }

  btle.hopChannel();
}


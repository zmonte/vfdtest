// vfd.ino

#include "vfd.h"

void resetVFD() {
  // Initialize all pins to known state LOW.
  for (int i = 0; i < 11; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  // Initial reset of display to get rid of any garbage from floating pins.
  digitalWrite(0, HIGH);
  delayMicroseconds(10);
  digitalWrite(0, LOW);
  digitalWrite(10, HIGH);
  delay(100); // TODO: 150?
}

/*
 * Sends a character to the VFD.
 */
void writeChar(char character) {
  // Deconstruct character into binary, then set parallel pins accordingly.
  for (int i = 0; i < 8; ++i) {
    digitalWrite(i + 2, (character >> i) & 1);
  }
  delayMicroseconds(USEC_DELAY);
  digitalWrite(10, LOW);
  delayMicroseconds(USEC_DELAY);
  digitalWrite(10, HIGH);
  delayMicroseconds(USEC_DELAY);
}

/*
 * Sends a string to the VFD.
 */
void writeStr(String str) {
  // Decontruct string into characters.
  for (unsigned int i = 0; i < str.length(); i++) {
    writeChar(str.charAt(i));
    delayMicroseconds(USEC_DELAY);
  }
}

/*
 * Sends a specified command to the VFD.
 * Commands are listed in vfd.h
 */
void writeCmd(unsigned int cmdCode) {
  for (int i = 0; i < 8; ++i) {
      digitalWrite(i + 2, (cmdCode >> i) & 1);
    }
    delayMicroseconds(USEC_DELAY);
    digitalWrite(10, LOW);
    delayMicroseconds(USEC_DELAY);
    digitalWrite(10, HIGH);
    delayMicroseconds(USEC_DELAY);
}

/*
 * Loops through all possible command bit combinations.
 * Used for discovering commands and characters.
 */
void cmdTest() {
  for (int i = 0; i < 511; i++) {
    writeCmd(i);
    delay(100);
  }
}

/*
 * Simple code example of how the VFD's parallel interface works.
 */
void parallelExample() {
  digitalWrite(2, HIGH);//1 -- LSB
  digitalWrite(3, HIGH);//2
  digitalWrite(4, LOW);//4
  digitalWrite(5, LOW);//8
  digitalWrite(6, HIGH);//1
  digitalWrite(7, LOW);//2
  digitalWrite(8, HIGH);//4
  digitalWrite(9, LOW);//8 -- MSB

  delayMicroseconds(USEC_DELAY);
  digitalWrite(10, LOW);
  delayMicroseconds(USEC_DELAY);
  digitalWrite(10, HIGH);
  delayMicroseconds(USEC_DELAY);
}

void setup() {
  resetVFD(); // Initial reset
  
  writeStr("test");
  writeCmd(CURSOR_BLINK);
}

void loop() {
  // put your main code here, to run repeatedly:

}


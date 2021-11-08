// This header file is in the public domain.

#ifndef Arduino_h
#define Arduino_h

#define ARDUINO 160
#define PROGMEM
#define FLASHMEM

#include "WProgram.h"
#include "pins_arduino.h"
#include <cstdio>

#define A16 0x116
#define INPUT_PULLUP		2

void delay(int ms);
void delayMicroseconds(int us);
void digitalWrite(int a, int b);
void analogWrite(int pin, int val);
bool digitalRead(uint8_t pin);
int analogRead(int pin);
void pinMode(uint8_t,uint8_t);
uint32_t millis();

int year();
int month();
int day();
int hour();
int minute();
int second();


class cSerial
{
  public:
  void println(const char* s);
  void print(const char* s);
  void printf(const char* x, ...);
  int available()
  {
    m_buff[0] = m_buff[0]== 0 ? 1 : 0;
    return m_buff[0];
  }
  void begin(int bRate) {m_bRate = bRate;}
  void write(char c);
  void write(const char* c);
  void write(const char* p, int len);


  char read();

private:
  char m_buff[1024];
  int m_bRate;
};

extern cSerial Serial;
extern cSerial Serial8;

#define pgm_read_byte(x) *(x)
#define OUTPUT 1
#define HIGH 1
#define LOW 0
#endif

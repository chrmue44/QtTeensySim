#include <chrono>
#include <ctime>
#include "Arduino.h"
#include <unistd.h>
#include <chrono>
#include <ctime>
#include "mainwindow.h"
#include <cstdio>
#include "InternalTemperature.h"

extern MainWindow* pw;

cEEPROM EEPROM;
cSerial Serial;
cSerial Serial8;

cInternalTemperature InternalTemperature;

void delay(int ms)
{

}

void delayMicroseconds(int us)
{

}

void analogWrite(int pin, int val)
{

}

int analogRead(int pin)
{
    return 111;
}

void digitalWrite(int a, int b)
{

}

void pinMode(uint8_t pin ,uint8_t mode)
{

}

bool digitalRead(uint8_t pin)
{
  return true;
}

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

uint32_t millis()
{
    auto t = std::chrono::system_clock::now();
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

  uint32_t retVal = static_cast<uint32_t>(millisec_since_epoch);
  return retVal;
}

uint delayMicros(uint us)
{
  usleep(us);
}

typedef std::chrono::system_clock Clock;

int year()
{
  auto now = Clock::now();
  std::time_t now_c = Clock::to_time_t(now);
  struct tm *parts = std::localtime(&now_c);
  return 1900 + parts->tm_year;
}

int month()
{
  auto now = Clock::now();
  std::time_t now_c = Clock::to_time_t(now);
  struct tm *parts = std::localtime(&now_c);
  return 1 + parts->tm_mon;
}

int day()
{
  auto now = Clock::now();
  std::time_t now_c = Clock::to_time_t(now);
  struct tm *parts = std::localtime(&now_c);
  return parts->tm_mday;
}

int hour()
{
  auto now = Clock::now();
  std::time_t now_c = Clock::to_time_t(now);
  struct tm *parts = std::localtime(&now_c);
  return parts->tm_hour;
}

int minute()
{
  auto now = Clock::now();
  std::time_t now_c = Clock::to_time_t(now);
  struct tm *parts = std::localtime(&now_c);
  return parts->tm_min;
}

int second()
{
  auto now = Clock::now();
  std::time_t now_c = Clock::to_time_t(now);
  struct tm *parts = std::localtime(&now_c);
  return parts->tm_sec;
}

void cEEPROM::write(int addr, uint8_t b)
{
  m_file = fopen("eeprom.bin", "r+b");
  if(m_file == nullptr)
    m_file = fopen("eeprom.bin", "w+b");
  fseek(m_file, addr, SEEK_SET);
  fwrite(&b, 1, 1, m_file);
  fclose(m_file);
};

uint8_t cEEPROM::read(int addr)
{
  uint8_t retVal = 0;
  m_file = fopen("eeprom.bin", "r+b");
  if(m_file == nullptr)
     m_file = fopen("eeprom.bin", "w+b");
  fseek(m_file, addr, SEEK_SET);
  fread(&retVal, 1, 1, m_file);
  fclose(m_file);
  return retVal;
}

void cSerial::println(const char* s)
{
  snprintf(m_buff, sizeof(m_buff),"%s\n", s);
  pw->log(m_buff,1);
}

void cSerial::print(const char* s)
{
  snprintf(m_buff, sizeof(m_buff), "%s", s);
  pw->log(m_buff,1);
}

void cSerial::printf(const char* fmt, ...)
{
  va_list vl;
  va_start(vl, fmt);
  snprintf(m_buff, sizeof(m_buff), fmt, vl);
  va_end(vl);
  pw->log(m_buff, 1);
}

void cSerial::write(char c)
{
  m_buff[0] = c;
  m_buff[1] = 0;
  pw->log(m_buff, 1);
}

void cSerial::write(const char* c)
{
  print(c);
}

void cSerial::write(const char* p, int len)
{
  for(int i = 0; i < len; i++)
  write(p[i]);
}

char cSerial::read()
{
  return 'a';
}

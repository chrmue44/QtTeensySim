#ifndef EEPROM_H
#define EEPROM_H
#include <cstdio>
#include <cstdint>

class cEEPROM
{
 public:
  void write(int addr, uint8_t b);
  uint8_t read(int addr);
 private:
  FILE* m_file;
};
extern cEEPROM EEPROM;

#endif // EEPROM_H

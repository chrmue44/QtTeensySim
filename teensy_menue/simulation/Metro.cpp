#include "Metro.h"
#include "Arduino.h"

Metro::Metro(int ms) :
    m_ms(ms)
{
  m_start = millis();
}

bool Metro::check()
{
  bool retVal = false;
  if(millis() > (m_start + m_ms))
  {
    retVal = true;
    m_start = millis();
  }
  return retVal;
}

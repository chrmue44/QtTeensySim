#include "Bounce.h"

Bounce::Bounce(int pin, int tim):
    m_pin(pin),
    m_time(tim),
    m_Edge(false)
{
}

void Bounce::createEdge()
{
  m_Edge = true;
}
bool Bounce::fallingEdge()
{
  bool retVal = m_Edge;
  m_Edge = false;
  return retVal;
}


#include "Encoder.h"

Encoder::Encoder(int pina, int pinb) :
m_pinA(pina),
m_pinB(pinb),
m_pos(0)
{
}

int Encoder::read()
{
    return m_pos;
}
void Encoder::incrementPos()
{
    m_pos += 4;
}
void Encoder::decrementPos()
{
    m_pos -= 4;
}


#ifndef METRO_H
#define METRO_H

#include <cstdint>
class Metro
{
public:
    Metro(int ms);
    bool check();
private:
   uint32_t m_ms;
   uint32_t m_start;
};

#endif // METRO_H

#ifndef BOUNCE_H
#define BOUNCE_H


class Bounce
{
public:
    Bounce(int pin, int tim);
    void update() {}
    void createEdge();
    bool fallingEdge();
 private:
   int m_pin;
   int m_time;
   bool m_Edge;
};

#endif // BOUNCE_H

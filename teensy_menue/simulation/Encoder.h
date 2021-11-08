#ifndef ENCODER_H
#define ENCODER_H


class Encoder
{
public:
    Encoder(int pina, int pinb);

    int read ();
    void incrementPos();
    void decrementPos();

 private:
  int m_pinA;
  int m_pinB;
  int m_pos;
};

#endif // ENCODER_H

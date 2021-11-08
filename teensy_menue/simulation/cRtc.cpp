/*************************************************************
 * BatSpy: Teensy 4.1 based recording device for bat sounds  *
 * ***********************************************************
 * Copyright (C) 2021 Christian Mueller                      *
 *                    chrmue44(AT)gmail{DOT}com              *
 * License: GNU GPLv3.0                                      *
 * ***********************************************************/

#include <Arduino.h>
#include "cRtc.h"



cRtc::cRtc()
{
}

void cRtc::setTime(int y, int mo, int d, int h, int m, int s)
{
}


int cRtc::getTime(int& y, int& mo, int& d, int& h, int& m, int& s)
{
 // tmElements_t tm;
 // time_t t = Teensy3Clock.get();
 // breakTime(t, tm);  // break time_t into elements
  y = year();
  if(y < 1970)
    y += 1970;
  mo = month();
  d = day();
  h = hour();
  m = minute();
  s = second();
  return 0;
}

time_t cRtc::getTime()
{
  time_t tUtc = time(nullptr);
  tm* tLoc  = localtime(&tUtc);
  tLoc->tm_gmtoff = 0;
  tLoc->tm_isdst = 0;
  time_t retVal= mktime(tLoc);
  return retVal;
}

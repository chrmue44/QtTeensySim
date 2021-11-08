#include "TinyGPS.h"

const float TinyGPS::GPS_INVALID_F_ANGLE = 1000.0;
const float TinyGPS::GPS_INVALID_F_ALTITUDE = 1000000.0;
const float TinyGPS::GPS_INVALID_F_SPEED = -1.0;

TinyGPS::TinyGPS()
    :
      _latitude(49.5 * 1000000),
      _longitude(8.5 * 1000000)
{

}

bool TinyGPS::encode(char c)
{
  return true;
}

void TinyGPS::get_position(long *latitude, long *longitude, unsigned long *fix_age)
{
   *latitude = _latitude;
   *longitude = _longitude;
    _latitude += 10;
    _longitude += 10;
   *fix_age = 0;
}

void TinyGPS::f_get_position(float *latitude, float *longitude, unsigned long *fix_age)
{
  long lat, lon;
  get_position(&lat, &lon, fix_age);
  *latitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lat / 1000000.0);
  *longitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lon / 1000000.0);
}

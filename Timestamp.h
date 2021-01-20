#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <ctime>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
inline std::string wr_to_string(long wr)
{
  time_t time = wr / 1e9;
  char* str = asctime(localtime(&time));
  std::string sstr(str);
  return sstr;
}

inline double wr_to_duration(long start, long stop)
{
  double duration = (stop - start) / 1e9;
  return duration;
}

inline std::string frequency(int counts, long duration)
{
  if (duration == 0)
  {
    return "0 Hz";
  }
  int hz = (counts / duration);
  int unit = hz;
  std::string suffix = "Hz";

  if (hz > 1e6)
  {
    unit /= 1e6;
    suffix = "MHz";
  }
  else if (hz > 1e3)
  {
    unit /= 1e3;
    suffix = "kHz";
  }

  std::stringstream s;
  s << std::setprecision(2) << unit << " " << suffix;
  return s.str();
}

#endif /* TIMESTAMP_H */

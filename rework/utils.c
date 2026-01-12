#include "philo.h"

long get_timestamp(void)
{
  long mstime;
  long seconds;
  long useconds;
  struct timeval current;

  gettimeofday(&current, NULL);
  seconds = current.tv_sec;
  useconds = current.tv_usec;
  mstime = ((seconds) * 1000 + useconds / 1000);
  return (mstime);
}
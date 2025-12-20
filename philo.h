#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
  pthread_t pth_id;
  int alive;
  pthread_mutex_t *fork1;
  pthread_mutex_t *fork2;
  int ph_num;
  long eat_time;
  long begin;
  long sleep_ms;
  long eat_ms;
  pthread_mutex_t *ph_data_tx;


} p_philo;


long get_timestamp(void);

#endif
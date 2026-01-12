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
  pthread_mutex_t *write;
  pthread_mutex_t *stop_lock;
  int *finish_simulation;
  pthread_mutex_t ph_data_tx;
  int ph_num;
  long eat_time;
  long begin;
  long sleep_ms;
  long eat_ms;
  int num_eats;

} p_philo;

typedef struct s_ctx
{
  int philos;
  long ttd;
  long tte;
  long tts;
  long begin_time;
  int eat_times;
  int write_init;
  int stop_lock_init;
  int finish_simulation;
  pthread_mutex_t write;
  pthread_mutex_t stop_lock;
} t_ctx;


#endif
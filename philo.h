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

typedef struct s_ctx
{
  int philos;
  long ttd;
  long tte;
  long tts;
  long eat_times;
  long beg_time;
} t_ctx;


// utils.c
int	ft_isprint(int c);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *s);

// ft_atoi.c
int	ft_atoi(const char *nptr);

long get_timestamp(void);

#endif
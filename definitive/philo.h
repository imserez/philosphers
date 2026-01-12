#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# include <stdio.h>

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
  long die_ms;
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

// ft_atoi
int	ft_atoi(const char *nptr);

// ft_utils
size_t	ft_strlen(const char *s);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
int	ft_isprint(int c);

// threads_monitor
void monitor_threads(p_philo *phs, t_ctx *ctx);

// philo.c
void safe_print(p_philo *ph, char *msg);
t_ctx *init_context(int argc, char **argv);
long get_timestamp(void);


// init_philo.c
int init_philo_data(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks);
int init_threads(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks);
int init_forks(t_ctx *ctx, pthread_mutex_t **forks);

// threads_routine.c
void *philo_routine(void *data);

// free_memory.c
int free_philos(p_philo **ph, int size, int mutex);
int free_forks(pthread_mutex_t **forks, int num);
int free_ctx(t_ctx **ctx);
int free_all(t_ctx **ctx, pthread_mutex_t **forks, p_philo **ph);

#endif
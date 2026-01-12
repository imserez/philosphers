#include "philo.h"

void destroy_mtx(p_philo *phs, pthread_mutex_t *forks, int n_ph)
{
  int i;

  i = -1;
  while (++i < n_ph)
  {
    pthread_mutex_destroy(phs[i].ph_data_tx);
    free(phs[i].ph_data_tx);
    phs[i].ph_data_tx = NULL;
    pthread_mutex_destroy(&forks[i]);
  }
  free(forks);
  free(phs);
}

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

void join_threads(p_philo *philos, int ph_num)
{
  while (ph_num > 0)
  {
    pthread_join(philos[ph_num - 1].pth_id, NULL);
    ph_num--;
  }
}
void kill_all(p_philo *phs, int num)
{
  int i;

  i = -1;
  while (++i < num)
  {
    pthread_mutex_lock(phs[i].ph_data_tx);
    phs[i].alive = 0;
    pthread_mutex_unlock(phs[i].ph_data_tx);
  }
}

void monitor_threads(p_philo *phs, pthread_mutex_t *forks, t_ctx *ctx)
{
    int i;
    long eat_time;

    while (1)
    {
        i = -1;
        while (++i < num)
        {
            pthread_mutex_lock(phs[i].ph_data_tx);
            eat_time = phs[i].eat_time;
            pthread_mutex_unlock(phs[i].ph_data_tx);
            if (get_timestamp() - eat_time > ctx->ttd)
            {
                printf("%ld The philo: %d died \n",get_timestamp() - phs[i].begin, phs[i].ph_num);
                kill_all(phs, ctx->philos);
                return ;
            }
        }
        usleep(100);
    }
}
void *philo_routine(void *data)
{
  int *count;
  p_philo *ph;
  ph = (p_philo *)data;
  int eat;
  int alive;

  alive = 1;
  while(1)
  {
    pthread_mutex_lock(ph->ph_data_tx);
    alive = ph->alive;
    pthread_mutex_unlock(ph->ph_data_tx);
    if (alive == 0)
      return NULL;
    if (pthread_mutex_trylock(ph->fork1) == 0)
    {
      eat = pthread_mutex_trylock(ph->fork2);
      if ( eat == 0)
      {
        pthread_mutex_lock(ph->ph_data_tx);
        ph->eat_time = get_timestamp();
        pthread_mutex_unlock(ph->ph_data_tx);
        printf("%ld, Philo %d eats\n", get_timestamp() - ph->begin, ph->ph_num);
        usleep(ph->eat_ms);
        pthread_mutex_unlock(ph->fork2);
        pthread_mutex_unlock(ph->fork1);
        usleep(ph->sleep_ms);
      }
      else
      {
        pthread_mutex_unlock(ph->fork1);
        usleep(10);
      }
    }

  }

  return (NULL);
}
#include "philo.h"


// ***
#include <stdio.h>
// ***

// each philo must be a thread
// one fork between each pair of philosophers
// each fork protected with a mutex
// only one philo, have access to one fork


// syntax is: num_philos, ttd, tte, tts, num_eat

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

int init_threads(int ph_num, p_philo **ph, pthread_mutex_t *forks, long begin)
{
  int created;
  int i;
  pthread_mutex_t *tmp;

  *ph = (p_philo *)malloc(ph_num * sizeof(p_philo));
  if (!*ph)
    return (0);

  i = 0;
  while (i < ph_num)
  {
    (*ph)[i].alive = 1;
    (*ph)[i].sleep_ms = 100000; // pass this
    (*ph)[i].eat_ms = 100;
    (*ph)[i].eat_time = get_timestamp();
    (*ph)[i].begin = begin;
    (*ph)[i].ph_num = i;
    (*ph)[i].ph_data_tx = malloc(sizeof(pthread_mutex_t));
    created = pthread_mutex_init((*ph)[i].ph_data_tx, NULL);

    // gettimeofday(&(*ph)[i].eat_time, NULL);
    (*ph)[i].fork1 = &forks[i];
    if (i == ph_num - 1)
      (*ph)[i].fork2 = &forks[0];
    else
      (*ph)[i].fork2 = &forks[i + 1];

    if (i % 2 == 0)
    {
      tmp = (*ph)[i].fork1;
      (*ph)[i].fork1 =  (*ph)[i].fork2;
      (*ph)[i].fork2 =  tmp;
    }

    created = pthread_create(&((*ph)[i]).pth_id, NULL, philo_routine, &((*ph)[i]));
    if (created != 0)
      return 0;
    i++;
  }
  return (1);
}

// int init_forks(int philos, pthread_mutex_t **forks)
// {
//   int fnum;
//   int i;
//   int created;

//   fnum = 3;
//   *forks = (pthread_mutex_t *)malloc(fnum * sizeof(pthread_mutex_t));
//   if (!*forks)
//     return 0;

//   i = 0;
//   while (i < fnum)
//   {
//     created = pthread_mutex_init(&((*forks)[i]), NULL);
//     i++;
//   }
//   return (1);
// }


// needs for ft_atoi!
// pass ms to the init threads, maybe
// split in prepare th & init th

void join_threads(p_philo *philos, int ph_num)
{
  while (ph_num > 0)
  {
    pthread_join(philos[ph_num - 1].pth_id, NULL);
    ph_num--;
  }
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

// int starvation(struct timeval eat, long maxms)
// {
//   long mstime;
//   long seconds;
//   long useconds;
//   struct timeval current;

//   gettimeofday(&current, NULL);
//   seconds = current.tv_sec - eat.tv_sec;
//   useconds = current.tv_usec - eat.tv_usec;
//   mstime = ((seconds) * 1000 + useconds / 1000.0);
//   return (mstime > maxms);
// }

void destroy_mtx(p_philo *phs, pthread_mutex_t *forks, int n_ph, int n_fk)
{
  int i;

  i = -1;
  while (++i < n_ph)
  {
    pthread_mutex_destroy(phs[i].ph_data_tx);
    free(phs[i].ph_data_tx);
    phs[i].ph_data_tx = NULL;
  }
  i = -1;
  while (++i < n_fk)
  {
    pthread_mutex_destroy(&forks[i]);
  }
  free(forks);
  free(phs);
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

void monitor_threads(p_philo *phs, pthread_mutex_t *forks, int num, long starve)
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

      // printf("the diff is: %ld \n", get_timestamp() - eat_time);
      if (get_timestamp() - eat_time  > starve)
      {
        printf("%ld The philo: %d died \n",get_timestamp() - phs[i].begin, phs[i].ph_num);
        kill_all(phs, num);
        return ;
      }
    }
    usleep(100);
  }
}

int main(int argc, char **argv)
{
  int th_init;
  int mx_init;
  long begin;
  p_philo *philosophers;
  pthread_mutex_t *forks;

  // begin = get_timestamp();

  // mx_init = init_forks(3, &forks);
  // th_init = init_threads(3, &philosophers, forks, begin);
  // monitor_threads(philosophers, forks, 3, 99);
  // join_threads(philosophers, 3);
  // destroy_mtx(philosophers, forks, 3, 3);
}
#include "philo.h"

static int sim_finished(p_philo *ph)
{
    int finished;
    pthread_mutex_lock(ph->stop_lock);
    finished = *(ph->finish_simulation);
    pthread_mutex_unlock(ph->stop_lock);
    return (finished);
}

static void *lonely_philo(p_philo *ph)
{
  usleep(ph->die_ms * 1000);
  pthread_mutex_unlock(ph->fork1);
  return (NULL);
}

static int do_eat(p_philo *ph)
{
  safe_print(ph, "has taken a fork");
  pthread_mutex_lock(&ph->ph_data_tx);
  ph->eat_time = get_timestamp();
  ph->num_eats++;
  pthread_mutex_unlock(&ph->ph_data_tx);
  safe_print(ph, "is eating");
  usleep(ph->eat_ms * 1000);
  pthread_mutex_unlock(ph->fork2);
  pthread_mutex_unlock(ph->fork1);
  return (0);
}

static int do_sleep(p_philo *ph)
{
  safe_print(ph, "is sleeping");
  usleep(ph->sleep_ms * 1000);
  return (0);
}

void *philo_routine(void *data)
{
    p_philo *ph;
    ph = (p_philo *)data;

    ph->eat_time = get_timestamp();
    while (1)
    {
        if (sim_finished(ph))
            return (NULL);
        if (pthread_mutex_lock(ph->fork1) == 0)
        {
            safe_print(ph, "has taken a fork");
            if (ph->fork1 == ph->fork2)
              return (lonely_philo(ph));
            if (pthread_mutex_lock(ph->fork2) == 0)
            {
              if (do_eat(ph))
                return (NULL);
              if (do_sleep(ph))
                return (NULL);
              safe_print(ph, "is thinking");
            }
        }
    }
    return (NULL);
}
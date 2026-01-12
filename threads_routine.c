#include "philo.h"

static int lonely_philo(p_philo *ph)
{
  pthread_mutex_lock(ph->fork1);
  safe_print(ph, "has taken a fork");
  usleep(ph->die_ms * 1000);
  pthread_mutex_unlock(ph->fork1);
  return (0);
}

static int sim_finished(p_philo *ph)
{
    int finished;
    pthread_mutex_lock(ph->stop_lock);
    finished = *(ph->finish_simulation);
    pthread_mutex_unlock(ph->stop_lock);
    return (finished);
}

static int prepare_routine(p_philo *ph)
{
  pthread_mutex_lock(&ph->ph_data_tx);
  ph->eat_time = get_timestamp();
  pthread_mutex_unlock(&ph->ph_data_tx);
  if (ph->fork1 == ph->fork2)
      return (lonely_philo(ph));
  return (1);
}

void *philo_routine(void *data)
{
    p_philo *ph;
    ph = (p_philo *)data;

    if (!prepare_routine(ph))
      return (NULL);
    if (ph->ph_num % 2 == 0)
      ft_usleep(ph->eat_ms / 10, ph);
    while (!sim_finished(ph))
    {
      if (!do_eat(ph))
        return (NULL);
      if (!do_sleep(ph))
        return (NULL);
      safe_print(ph, "is thinking");
      if (ph->philos % 2 != 0)
        safe_gap(ph);
    }
    return (NULL);
}
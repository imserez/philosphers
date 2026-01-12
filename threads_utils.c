#include "philo.h"



int do_eat(p_philo *ph)
{
  pthread_mutex_lock(ph->fork1);
  if (safe_print(ph, "has taken a fork"))
  {
    pthread_mutex_unlock(ph->fork1);
    return (0);
  }
  pthread_mutex_lock(ph->fork2);
  if (safe_print(ph, "has taken a fork"))
  {
    pthread_mutex_unlock(ph->fork2);
    pthread_mutex_unlock(ph->fork1);
    return (0);
  }
  pthread_mutex_lock(&ph->ph_data_tx);
  ph->eat_time = get_timestamp();
  ph->num_eats++;
  pthread_mutex_unlock(&ph->ph_data_tx);
  safe_print(ph, "is eating");
  ft_usleep(ph->eat_ms, ph);
  pthread_mutex_unlock(ph->fork2);
  pthread_mutex_unlock(ph->fork1);
  return (1);
}

int do_sleep(p_philo *ph)
{
  if (safe_print(ph, "is sleeping"))
    return (0);
  ft_usleep(ph->sleep_ms, ph);
  return (1);
}

void safe_gap(p_philo *ph)
{
  long think_time;

  think_time = ph->eat_ms * 2 - ph->sleep_ms;
  if (think_time < 0)
    think_time = 0;
  ft_usleep(think_time * 0.4, ph);
}

int ft_usleep(size_t milliseconds, p_philo *ph)
{
    size_t start;

    start = get_timestamp();
    while ((get_timestamp() - start) < milliseconds)
    {
        if (sim_finished(ph))
            return (1);
        usleep(500); // Duerme 0.5ms para no saturar la CPU
    }
    return (0);
}
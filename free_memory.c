#include "philo.h"

int free_all(t_ctx **ctx, pthread_mutex_t **forks, p_philo **ph)
{
    (*ctx)->finish_simulation = 1;
    free_forks(forks, (*ctx)->philos);
    free_philos(ph, (*ctx)->philos, 0);
    free_ctx(ctx);
    return (1);
}

int free_philos(p_philo **ph, int size, int mutex)
{
    int i;

    if (!ph || !(*ph))
        return (1);
    i = -1;
    while (++i < size)
    {
        if (mutex == 0)
            pthread_mutex_destroy(&(*ph)[i].ph_data_tx);
        else if (i != size - 1)
            pthread_mutex_destroy(&(*ph)[i].ph_data_tx);
    }
    return (1);
}

int free_ctx(t_ctx **ctx)
{
    if (!ctx || !(*ctx))
        return (1);
    if ((*ctx)->write_init)
        pthread_mutex_destroy(&(*ctx)->write);
    if ((*ctx)->stop_lock_init)
        pthread_mutex_destroy(&(*ctx)->stop_lock);
    free(*ctx);
    *ctx = NULL;
    return (1);
}

int free_forks(pthread_mutex_t **forks, int num)
{
    int i;

    if (!forks ||!(*forks))
        return (1);
    i = 0;
    while (i < num)
    {
        pthread_mutex_destroy(&((*forks)[i]));
        i++;
    }
    free(*forks);
    *forks = NULL;
    return (1);
}
#include "philo.h"


void safe_print(p_philo *ph, char *msg)
{
    long time;

    pthread_mutex_lock(ph->write);
    pthread_mutex_lock(ph->stop_lock);
    if (!(*ph->finish_simulation))
    {
        time = get_timestamp() - ph->begin;
        // write(1, msg, ft_strlen(msg));
        printf("%ld %d %s\n", time, ph->ph_num + 1, msg);
    }
    pthread_mutex_unlock(ph->stop_lock);
    pthread_mutex_unlock(ph->write);

}

void stop_sim(t_ctx *ctx)
{
  pthread_mutex_lock(&ctx->stop_lock);
  ctx->finish_simulation = 1;
  pthread_mutex_unlock(&ctx->stop_lock);
}

static void safe_dead_print(p_philo *ph, char *msg)
{
    long time;

    pthread_mutex_lock(ph->write);
    pthread_mutex_lock(ph->stop_lock);
    if (!(*ph->finish_simulation))
    {
        time = get_timestamp() - ph->begin;
        // write(1, msg, ft_strlen(msg));
        printf("%ld %d %s\n", time, ph->ph_num + 1, msg);
        *ph->finish_simulation = 1;
    }
    pthread_mutex_unlock(ph->stop_lock);
    pthread_mutex_unlock(ph->write);

}



int sim_finished(p_philo *ph)
{
    int finished;
    pthread_mutex_lock(ph->stop_lock);
    finished = *(ph->finish_simulation);
    pthread_mutex_unlock(ph->stop_lock);
    return (finished);
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
            {
                usleep(ph->die_ms * 1000);
                pthread_mutex_unlock(ph->fork1);
                return (NULL);
            }
            if (pthread_mutex_lock(ph->fork2) == 0)
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
                if (sim_finished(ph))
                    return (NULL);
                safe_print(ph, "is sleeping");
                usleep(ph->sleep_ms * 1000);
                if (sim_finished(ph))
                    return (NULL);
                safe_print(ph, "is thinking");
            }
        }
    }
    return (NULL);
}

int is_alive(p_philo *phs, t_ctx *ctx, int i, int *num_eats)
{
    long last_eat_time;

    pthread_mutex_lock(&phs[i].ph_data_tx);
    last_eat_time = phs[i].eat_time;
    *num_eats = phs[i].num_eats;
    pthread_mutex_unlock(&phs[i].ph_data_tx);
    if (get_timestamp() - last_eat_time > ctx->ttd)
    {
        safe_dead_print(&phs[i], "died");
        stop_sim(ctx);
        return (0);
    }
    return (1);
}

void monitor_threads(p_philo *phs, t_ctx *ctx)
{
    int i;
    int full_eat;
    int num_eats;

    while (1)
    {
        i = -1;
        full_eat = 0;
        while(++i < ctx->philos)
        {
            if (!is_alive(phs, ctx, i, &num_eats))
                return ;
            if (ctx->eat_times != -1 && num_eats >= ctx->eat_times)
                full_eat++;
        }
        if (full_eat == ctx->philos)
        {
            stop_sim(ctx);
            return ;
        }
        usleep(1000);
    }
}
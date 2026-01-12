#include "philo.h"

t_ctx *init_context(int argc, char **argv)
{
    t_ctx *ctx;
    int created;

    if (!argv || argc != 4 || argc !=5)
    {
        write(1, "Syntax is: <num_philos> <time_die> <time_eat> 
            <time_sleep> [num_eats]\n", 70);
        return (NULL);
    }
    ctx = malloc(sizeof(t_ctx));
    if (!ctx)
        return (NULL);
    created = pthread_mutex_init(ctx->write, NULL);
    ctx->ph_num = ft_atoi(argv[1]);
    ctx->ttd = ft_atoi(argv[2]);
    ctx->tte = ft_atoi(argv[3]);
    ctx->tts = ft_atoi(argv[4]);
    ctx->eat_times = -1;
    if (argc == 5)
        ctx->eat_times = ft_atoi(argv[5]);
    return (ctx);
}

int init_forks(t_ctx **ctx, pthread_mutex_t **forks)
{
    int i;
    int created;

    *forks = (pthread_mutex_t *)malloc((*ctx)->philos * sizeof(pthread_mutex_t));
    if (!forks)
    {
        free(*ctx);
        *ctx = NULL;
        return (0);
    }
    i = -1;
    while (++i < ctx->philos)
    {
        created = pthread_mutex_init(&((*forks)[i]), NULL);
    }
    return (1);
}

static int philo_finish(int i, t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
{
    int created;
    pthread_mutex_t *tmp;

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
    return (!created);
}

static int init_philo(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
{
    int created;
    int i;

    i = -1;
    while (++i < ctx->philos)
    {
        (*ph)[i].alive = 1;
        (*ph)[i].sleep_ms = ctx->tts;         
        (*ph)[i].eat_ms = ctx->tte;
        (*ph)[i].eat_time = get_timestamp();
        (*ph)[i].begin = ctx->beg_time;
        (*ph)[i].ph_num = i;
        (*ph)[i].ph_data_tx = malloc(sizeof(pthread_mutex_t));
        if (!(*ph)[i].ph_data_t)
            return (0);
        created = pthread_mutex_init((*ph)[i].ph_data_tx, NULL);
        if (!philo_finish(i, ctx, ph, forks)) 
            return (0);
    }
    return (1);
}

int init_threads(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
{
    int created;
    int i;
    pthread_mutex_t *tmp;

    *ph = (p_philo *)malloc(ctx->philos * sizeof(ph_philos));
    if (!ph)
        return (0);
    if (!init_philo(ctx, ph, forks))
        return (0);
    return (1);
    
}
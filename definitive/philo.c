#include "philo.h"

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

static void parse_arg_values(int argc, char **argv, t_ctx *ctx)
{
    ctx->philos = ft_atoi(argv[1]);
    ctx->ttd = ft_atoi(argv[2]);
    ctx->tte = ft_atoi(argv[3]);
    ctx->tts = ft_atoi(argv[4]);
    ctx->eat_times = -1;
    ctx->finish_simulation = 0;
    if (argc == 6)
        ctx->eat_times = ft_atoi(argv[5]);
}

t_ctx *init_context(int argc, char **argv)
{
    t_ctx *ctx;

    if (!argv || (argc != 5 && argc != 6))
    {
        // write(1, "Syntax is: <num_philos> <time_die> <time_eat> <time_sleep> [num_eats]\n", 70);
        return (NULL);
    }
    ctx = (t_ctx *)malloc(sizeof(t_ctx));
    if (ctx)
    {
        ctx->write_init = 0;
        ctx->stop_lock_init = 0;
        if (pthread_mutex_init(&ctx->write, NULL) != 0)
            return (free_ctx(&ctx), NULL);
        ctx->write_init = 1;
        if (pthread_mutex_init(&ctx->stop_lock, NULL) != 0)
            return (free_ctx(&ctx), NULL);
        ctx->stop_lock_init = 1;
        parse_arg_values(argc, argv, ctx);
    }
    return (ctx);
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

int init_forks(t_ctx *ctx, pthread_mutex_t **forks)
{
    int i;
    int j;

    *forks = (pthread_mutex_t *)malloc(ctx->philos * sizeof(pthread_mutex_t));
    if (!(*forks))
        return (0);
    i = -1;
    while (++i < ctx->philos)
    {
        if (pthread_mutex_init(&((*forks)[i]), NULL) != 0)
        {
            j = -1;
            while (++j < i)
                pthread_mutex_destroy(&((*forks)[j]));
            free(*forks);
            return (0);
        }
    }
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
}

static int philo_init_pipeline(int i, t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
{
    int created;
    pthread_mutex_t *tmp;

    (*ph)[i].fork1 = &forks[i];
    if (i == ctx->philos - 1)
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

int init_philo_data(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
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
        (*ph)[i].num_eats = 0;
        (*ph)[i].write = &ctx->write;
        (*ph)[i].stop_lock = &ctx->stop_lock;
        (*ph)[i].finish_simulation = &ctx->finish_simulation;
        if (pthread_mutex_init(&((*ph)[i].ph_data_tx), NULL) != 0)
            return (free_philos(ph, i, 1));
        if (!philo_init_pipeline(i, ctx, ph, forks)) 
            return (free_philos(ph, i, 0));
    }
    return (1);
}

int init_threads(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
{
    *ph = (p_philo *)malloc(sizeof(p_philo) * ctx->philos);
    if (!(*ph))
        return (0);
    if (!init_philo_data(ctx, ph, forks))
        return (0);
}

int free_all(t_ctx **ctx, pthread_mutex_t **forks, p_philo **ph)
{
    (*ctx)->finish_simulation = 1;
    free_forks(forks, ctx->philos);
    free_philos(ph, ctx->philos, 0);
    free_ctx(ctx);
    return (1);
}

int main(int argc, char **argv)
{
    t_ctx *ctx;
    pthread_mutex_t *forks;
    p_philo *ph;

    ctx = init_context(argc, argv);
    if (!ctx)
        return (1);
    ctx->begin_time = get_timestamp();
    if (!init_forks(ctx, &forks))
        return(free_ctx(&ctx));
    if (!init_threads(ctx, &ph, forks))
        return (free_all(&ctx, &forks, &ph));
    monitor_threads(ph, forks, ctx);
}
#include "philo.h"


// int init_context(t_ctx *ctx, int argc, char **argv)
// {
//     if (!argv || argc != 4 || argc !=5)
//     {
//         write(1, "Syntax is: <num_philos> <time_die> <time_eat> <time_sleep> [num_eats]\n", 70);
//         return (0);
//     }
//     ctx = malloc(sizeof(t_ctx));
//     if (!ctx)
//         return (0);
//     ctx->ph_num = ft_atoi(argv[1]);
//     ctx->ttd = ft_atoi(argv[2);
//     ctx->tte = ft_atoi(argv[3]);
//     ctx->tts = ft_atoi(argv[4]);
//     ctx->eat_times = -1;
//     if (argc == 5)
//         ctx->eat_times = ft_atoi(argv[5]);
//     return (1);
// }

// int init_forks(t_ctx **ctx, pthread_mutex_t **forks)
// {
//     int i;
//     int created;

//     *forks = (pthread_mutex_t *)malloc((*ctx)->philos * sizeof(pthread_mutex_t));
//     if (!forks)
//     {
//         free(*ctx);
//         *ctx = NULL;
//         return (0);
//     }
//     i = -1;
//     while (++i < ctx->philos)
//         created = pthread_mutex_init(&((*forks)[i]), NULL);
//     return (1);
// }

// int safe_exit_ret(t_ctx **ctx, p_philo **phs)
// {
//     int i;

//     if (ctx && *ctx)
//     {
//         free(*ctx);
//         *ctx = NULL;
//     }
//     i = -1;
//     if (phs && *phs)
//     {
//         while (phs[++i])
//         {
//             if ((*phs)[i].ph_data_tx)
//                 free((*phs)[i].ph_data_tx);
//             (*phs)[i].ph_data_tx = NULL;
//         }
//     }
//     if (*phs)
//         free(*phs);
//     *phs = NULL;
//     return (1);
// }

int main(int argc, char **argv)
{
    pthread_mutex_t *forks;
    t_ctx *ctx;
    p_philo *philos;

    // if (!init_context(ctx, argc, argv))
    //     return (1);
    // ctx.beg_time = get_timestamp();
    // if (!init_forks(&ctx, &forks));
    //     return (1);
    // if (!init_threads(ctx, philos))
    //     return (safe_exit_ret(&ctx, &philos))
    monitor_threads(philos, forks, ctx);
    join_threads(philos, ctx->philos);
    destroy_mtx(philos, forks, ctx->philos)

}
#include "philo.h"


// static int philo_finish(int i, t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
// {
//     int created;
//     pthread_mutex_t *tmp;

//     (*ph)[i].fork1 = &forks[i];
//     if (i == ph_num - 1)
//       (*ph)[i].fork2 = &forks[0];
//     else
//       (*ph)[i].fork2 = &forks[i + 1];
//     if (i % 2 == 0)
//     {
//       tmp = (*ph)[i].fork1;
//       (*ph)[i].fork1 =  (*ph)[i].fork2;
//       (*ph)[i].fork2 =  tmp;
//     }
//     created = pthread_create(&((*ph)[i]).pth_id, NULL, philo_routine, &((*ph)[i]));
//     return (!created);
// }

// static int init_philo(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
// {
//     int created;
//     int i;

//     i = -1;
//     while (++i < ctx->philos)
//     {
//         (*ph)[i].alive = 1;
//         (*ph)[i].sleep_ms = ctx->tts; // pass this
//         (*ph)[i].eat_ms = ctx->tte;
//         (*ph)[i].eat_time = get_timestamp();
//         (*ph)[i].begin = begin;
//         (*ph)[i].ph_num = i;
//         (*ph)[i].ph_data_tx = malloc(sizeof(pthread_mutex_t));
//         if (!(*ph)[i].ph_data_t)
//             return (0);
//         created = pthread_mutex_init((*ph)[i].ph_data_tx, NULL);
//         if (!philo_finish(i, ctx, ph, forks)) 
//             return (0);
//     }
//     return (1);
// }


// int init_threads(t_ctx *ctx, p_philo **ph, pthread_mutex_t *forks)
// {
//     int created;
//     int i;
//     pthread_mutex_t *tmp;

//     *ph = (p_philo *)malloc(ctx->philos * sizeof(ph_philos));
//     if (!ph)
//         return (0);
//     if (!init_philo(ctx, ph, forks))
//         return (0);
//     return (1);
    
// }
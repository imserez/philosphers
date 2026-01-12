#include "philo.h"

int safe_exit_ret(t_ctx **ctx, p_philo **phs)
{
    int i;

    if (ctx && *ctx)
    {
        free(*ctx);
        *ctx = NULL;
    }
    i = -1;
    if (phs && *phs)
    {
        while (phs[++i])
        {
            if ((*phs)[i].ph_data_tx)
                free((*phs)[i].ph_data_tx);
            (*phs)[i].ph_data_tx = NULL;
        }
    }
    if (*phs)
        free(*phs);
    *phs = NULL;
    return (1);
}

int main(int argc, char **argv)
{
    t_ctx *ctx;
    pthread_mutex_t *forks;
    p_philo *philos;
    
    ctx = init_context(argc, argv);
    if (!ctx)
        return (0);
    ctx.beg_time = get_timestamp();
    if (!init_forks(&ctx, &forks));
        return (1);
    if (!init_threads(ctx, philos))
        return (safe_exit_ret(&ctx, &philos))
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:48:59 by serez             #+#    #+#             */
/*   Updated: 2026/01/13 10:59:17 by serez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_sim(t_ctx *ctx)
{
	pthread_mutex_lock(&ctx->stop_lock);
	ctx->finish_simulation = 1;
	pthread_mutex_unlock(&ctx->stop_lock);
}

static void	safe_dead_print(t_philo *ph, char *msg)
{
	long	time;

	pthread_mutex_lock(ph->write);
	pthread_mutex_lock(ph->stop_lock);
	if (!(*ph->finish_simulation))
	{
		time = get_timestamp() - ph->begin;
		printf("%ld %d %s\n", time, ph->ph_num + 1, msg);
		*ph->finish_simulation = 1;
	}
	pthread_mutex_unlock(ph->stop_lock);
	pthread_mutex_unlock(ph->write);
}

static int	is_alive(t_philo *phs, t_ctx *ctx, int i, int *num_eats)
{
	long	last_eat_time;

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

void	monitor_threads(t_philo *phs, t_ctx *ctx)
{
	int	i;
	int	full_eat;
	int	num_eats;

	while (1)
	{
		i = -1;
		full_eat = 0;
		while (++i < ctx->philos)
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

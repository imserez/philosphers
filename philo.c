/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:46:48 by serez             #+#    #+#             */
/*   Updated: 2026/01/13 10:59:24 by serez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(void)
{
	long			mstime;
	long			seconds;
	long			useconds;
	struct timeval	current;

	gettimeofday(&current, NULL);
	seconds = current.tv_sec;
	useconds = current.tv_usec;
	mstime = ((seconds) * 1000 + useconds / 1000);
	return (mstime);
}

int	safe_print(t_philo *ph, char *msg)
{
	long	time;
	int		stop;

	pthread_mutex_lock(ph->write);
	pthread_mutex_lock(ph->stop_lock);
	stop = *ph->finish_simulation;
	if (!stop)
	{
		time = get_timestamp() - ph->begin;
		printf("%ld %d %s\n", time, ph->ph_num + 1, msg);
	}
	pthread_mutex_unlock(ph->stop_lock);
	pthread_mutex_unlock(ph->write);
	return (stop);
}

void	join_threads(t_philo *phs, int num)
{
	while (num > 0)
	{
		pthread_join(phs[num - 1].pth_id, NULL);
		num--;
	}
}

int	main(int argc, char **argv)
{
	t_ctx				*ctx;
	pthread_mutex_t		*forks;
	t_philo				*ph;

	ctx = init_context(argc, argv);
	if (!ctx)
		return (1);
	if (!validate_input(ctx, argc))
		return (free_ctx(&ctx));
	ctx->begin_time = get_timestamp();
	if (!init_forks(ctx, &forks))
		return (free_ctx(&ctx));
	if (!init_threads(ctx, &ph, forks))
		return (free_all(&ctx, &forks, &ph));
	monitor_threads(ph, ctx);
	join_threads(ph, ctx->philos);
	free_all(&ctx, &forks, &ph);
}

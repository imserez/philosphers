/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:39:03 by serez             #+#    #+#             */
/*   Updated: 2026/01/15 19:28:26 by sjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_init_pipeline(int i, t_ctx *ctx, t_philo **ph,
				pthread_mutex_t *forks)
{
	pthread_mutex_t	*tmp;

	(*ph)[i].fork1 = &forks[i];
	if (i == ctx->philos - 1)
		(*ph)[i].fork2 = &forks[0];
	else
		(*ph)[i].fork2 = &forks[i + 1];
	if (i % 2 == 1)
	{
		tmp = (*ph)[i].fork1;
		(*ph)[i].fork1 = (*ph)[i].fork2;
		(*ph)[i].fork2 = tmp;
	}
	return (1);
}

int	init_threads(t_ctx *ctx, t_philo **ph, pthread_mutex_t *forks)
{
	*ph = (t_philo *)malloc(sizeof(t_philo) * ctx->philos);
	if (!(*ph))
		return (0);
	if (!init_philo_data(ctx, ph, forks))
		return (0);
	return (1);
}

int	init_forks(t_ctx *ctx, pthread_mutex_t **forks)
{
	int	i;
	int	j;

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

static int	launch_threads(t_ctx *ctx, t_philo **ph)
{
	int	created;
	int	i;

	i = -1;
	ctx->begin_time = get_timestamp();
	while (++i < ctx->philos)
	{
		(*ph)[i].begin = ctx->begin_time;
		created = pthread_create(&((*ph)[i]).pth_id, NULL,
				philo_routine, &((*ph)[i]));
		if (created != 0)
			return (free_philos(ph, i, 0), 0);
	}
	return (1);
}

int	init_philo_data(t_ctx *ctx, t_philo **ph, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < ctx->philos)
	{
		(*ph)[i].alive = 1;
		(*ph)[i].sleep_ms = ctx->tts;
		(*ph)[i].eat_ms = ctx->tte;
		(*ph)[i].eat_time = get_timestamp();
		(*ph)[i].ph_num = i;
		(*ph)[i].philos = ctx->philos;
		(*ph)[i].die_ms = ctx->ttd;
		(*ph)[i].num_eats = 0;
		(*ph)[i].write = &ctx->write;
		(*ph)[i].stop_lock = &ctx->stop_lock;
		(*ph)[i].finish_simulation = &ctx->finish_simulation;
		if (pthread_mutex_init(&((*ph)[i].ph_data_tx), NULL) != 0)
			return (free_philos(ph, i, 1));
		philo_init_pipeline(i, ctx, ph, forks);
	}
	return (launch_threads(ctx, ph));
}

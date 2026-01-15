/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:53:50 by serez             #+#    #+#             */
/*   Updated: 2026/01/15 19:23:16 by sjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_eat(t_philo *ph)
{
	pthread_mutex_lock(ph->fork1);
	if (safe_print(ph, "has taken a fork"))
	{
		pthread_mutex_unlock(ph->fork1);
		return (0);
	}
	pthread_mutex_lock(ph->fork2);
	if (safe_print(ph, "has taken a fork"))
	{
		pthread_mutex_unlock(ph->fork2);
		pthread_mutex_unlock(ph->fork1);
		return (0);
	}
	pthread_mutex_lock(&ph->ph_data_tx);
	ph->eat_time = get_timestamp();
	ph->num_eats++;
	pthread_mutex_unlock(&ph->ph_data_tx);
	safe_print(ph, "is eating");
	ft_usleep(ph->eat_ms, ph);
	pthread_mutex_unlock(ph->fork2);
	pthread_mutex_unlock(ph->fork1);
	return (1);
}

int	do_sleep(t_philo *ph)
{
	if (safe_print(ph, "is sleeping"))
		return (0);
	ft_usleep(ph->sleep_ms, ph);
	return (1);
}

int	sim_finished(t_philo *ph)
{
	int	finished;

	pthread_mutex_lock(ph->stop_lock);
	finished = *(ph->finish_simulation);
	pthread_mutex_unlock(ph->stop_lock);
	return (finished);
}

void	safe_gap(t_philo *ph)
{
	ft_usleep(30, ph);
}

int	ft_usleep(size_t milliseconds, t_philo *ph)
{
	size_t	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < milliseconds)
	{
		if (sim_finished(ph))
			return (1);
		usleep(500);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:57:41 by serez             #+#    #+#             */
/*   Updated: 2026/01/13 10:57:45 by serez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_t		pth_id;
	int				alive;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	*write;
	pthread_mutex_t	*stop_lock;
	int				*finish_simulation;
	pthread_mutex_t	ph_data_tx;
	int				ph_num;
	int				philos;
	long			eat_time;
	long			begin;
	long			sleep_ms;
	long			eat_ms;
	long			die_ms;
	int				num_eats;

}					t_philo;

typedef struct s_ctx
{
	int				philos;
	long			ttd;
	long			tte;
	long			tts;
	long			begin_time;
	int				eat_times;
	int				write_init;
	int				stop_lock_init;
	int				finish_simulation;
	pthread_mutex_t	write;
	pthread_mutex_t	stop_lock;
}					t_ctx;

// parse_input.c
t_ctx	*init_context(int argc, char **argv);
int		validate_input(t_ctx *ctx, int argc);

// ft_atoi.c
int		ft_atoi(const char *nptr);

// ft_utils.c
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isprint(int c);

// threads_monitor.c
void	monitor_threads(t_philo *phs, t_ctx *ctx);

// philo.c
int		safe_print(t_philo *ph, char *msg);
long	get_timestamp(void);

// init_philo.c
int		init_philo_data(t_ctx *ctx, t_philo **ph, pthread_mutex_t *forks);
int		init_threads(t_ctx *ctx, t_philo **ph, pthread_mutex_t *forks);
int		init_forks(t_ctx *ctx, pthread_mutex_t **forks);

// threads_routine.c
void	*philo_routine(void *data);

// threads_utils.c
int		ft_usleep(size_t milliseconds, t_philo *ph);
void	safe_gap(t_philo *ph);
int		do_sleep(t_philo *ph);
int		do_eat(t_philo *ph);
int		sim_finished(t_philo *ph);

// free_memory.c
int		free_philos(t_philo **ph, int size, int mutex);
int		free_forks(pthread_mutex_t **forks, int num);
int		free_ctx(t_ctx **ctx);
int		free_all(t_ctx **ctx, pthread_mutex_t **forks, t_philo **ph);

#endif

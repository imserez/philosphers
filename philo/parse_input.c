/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:43:11 by serez             #+#    #+#             */
/*   Updated: 2026/01/15 17:26:08 by sjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_arg_values(int argc, char **argv, t_ctx *ctx)
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

t_ctx	*init_context(int argc, char **argv)
{
	t_ctx	*ctx;

	if (!argv || (argc != 5 && argc != 6))
	{
		write(1, "Syntax is: <num_philos> <time_die> ", 35);
		write(1, "<time_eat> <time_sleep> [num_eats]\n", 35);
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

int	validate_input(t_ctx *ctx, int argc)
{
	if (ctx->philos < 1 || ctx->ttd < 0 || ctx->tte < 0 || ctx->tts < 0)
	{
		write(1, "Invalid parameters. Must be positive.\n", 39);
		return (0);
	}
	if (argc == 6 && ctx->eat_times < 1)
	{
		write(1, "Invalid parameters. Must be positive.\n", 39);
		return (0);
	}
	return (1);
}

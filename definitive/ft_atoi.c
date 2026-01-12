/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuarez <sjuarez@student.42.barcelona>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:48:50 by sjuarez           #+#    #+#             */
/*   Updated: 2025/10/01 21:13:41 by sjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	find_negative(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] != '\0' && !ft_isdigit(nptr[i]))
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	return (1);
}

static int	find_first_num(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] != '\0')
	{
		if (ft_isdigit(nptr[i]))
			return (i);
		i++;
	}
	return (i);
}

static int	invalid_seq(const char *nptr, int limit)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	while (nptr[i] != '\0' && i < limit)
	{
		if (!ft_isdigit(nptr[i]))
			count++;
		if (ft_isalpha(nptr[i]) || !ft_isprint(nptr[i]))
			return (1);
		i++;
	}
	return (count > 1);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	len;
	int	i;

	i = 0 + find_first_num(nptr);
	len = ft_strlen(nptr);
	result = 0;
	if (invalid_seq(nptr, i))
		return (0);
	while (i < len)
	{
		if (!ft_isdigit(nptr[i]))
			break ;
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	return (result * find_negative(nptr));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuarez <sjuarez@student.42.barcelona>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:48:50 by sjuarez           #+#    #+#             */
/*   Updated: 2026/01/14 10:38:17 by serez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	long	result;
	int	i;
	int	negative;

	i = 0;
	while (nptr[i] && (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	negative = 0;
	if (nptr[i] && nptr[i] == '-')
		negative = 1;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
		i++;
	if (nptr[i] == '\0')
		return (-1);
	result = 0;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9' || result < 0)
			return (-1);
		result = result * 10 + (nptr[i++] - '0');
		if (result > (long)INT_MAX || (result > (long)INT_MIN && negative))
			return (-1);
	}
	return (result * (negative * -2 + 1));
}

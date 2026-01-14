/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuarez <sjuarez@student.42.barcelona>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:48:50 by sjuarez           #+#    #+#             */
/*   Updated: 2026/01/14 15:35:15 by serez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	long	result;
	int		i;

	i = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r')))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
		i++;
	if (nptr[i] == '\0' || (i > 0 && nptr[i - 1] == '-'))
		return (-1);
	result = 0;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9' || result < 0)
			return (-1);
		result = result * 10 + (nptr[i++] - '0');
		if (result > (long)INT_MAX)
			return (-1);
	}
	return ((int)result);
}

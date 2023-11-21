/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:29:19 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/21 12:29:19 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		j;
	long	k;

	i = 0;
	k = 0;
	j = 1;
	while (ft_isspace(str[i]))
		i++;
	if ((str[i + 1] >= 48) && (str[i + 1] <= 57) && \
		((str[i] == '-') || (str[i] == '+')))
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		k = k * 10;
		k = k + str[i] - 48;
		i++;
	}
	return (j * k);
}

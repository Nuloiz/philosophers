/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:22:17 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/22 11:22:17 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time(t_info_i *input)
{
	unsigned long long	miliseconds;
	struct timeval		time;

	gettimeofday(&time, NULL);
	miliseconds = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	miliseconds = miliseconds - input->start_time;
	return (miliseconds);
}

unsigned long long	start_time(void)
{
	unsigned long long	miliseconds;
	struct timeval		time;

	gettimeofday(&time, NULL);
	miliseconds = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	return (miliseconds);
}
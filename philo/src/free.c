/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:08:43 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/23 10:08:43 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_every(t_info_i input)
{
	int	i;

	i = 0;
	while (i < input.count)
	{
		pthread_mutex_destroy(&(input.forks[i]));
		pthread_join((input.thread[i]), NULL);
		i++;
	}
	pthread_mutex_destroy(&(input.print_m));
	free(input.philos);
	free(input.thread);
	free(input.forks);
}

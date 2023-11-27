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
	int i;

	i = 0;
	while (i < input.count)
	{
		pthread_mutex_destroy(&(input.forks[i]));
		pthread_join((input.thread[i]), NULL);
		i++;
	}
	free(input.philos);
	free(input.thread);
	free(input.forks);
}

void	someone_died(t_info_i *input)
{
	int	j;

	j = 0;
	while (j < input->count)
	{
		input->philos[j].kill = 1;
		j++;
	}
	free_every(*input);
}
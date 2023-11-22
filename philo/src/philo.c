/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:08:19 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/21 14:08:19 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef void*	(*t_thread_func)(void	*);

static void	*threading(t_info_i *input)
{
	int	i;

	i = 0;
	while (1)
	{
		if (input->must_eat > -1 && input->must_eat == i)
			break ;
		printf("eats\n");
		usleep(input->eat);
		printf("sleeps\n");
		usleep(input->sleep);
		if (input->eat + input->sleep >= input->die)
		{
			printf("dies\n");
			break ;
		}
		i++;
	}
	return ((void *)input);
}

int	philo(t_info_i input)
{
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;
	int				i;

	threads = ft_calloc(sizeof(pthread_t), input.count);
	mutexes = ft_calloc(sizeof(pthread_mutex_t), input.count);
	i = 0;
	printf("Input.count: %d\n", (int)input.count);
	while (i < (int)input.count)
	{
		printf("Philosopher: %d\n", i);
		pthread_mutex_init(&(mutexes[i]), NULL);
		pthread_create(&(threads[i]), NULL, (t_thread_func)threading, (void *)&input);
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}

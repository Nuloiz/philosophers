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

static void	*threading(t_philo *input)
{
	int					i;
	unsigned long long	meal;

	i = 0;
	meal = 0;
	while (1)
	{
		if (input->must_eat > -1 && input->must_eat == i)
			break ;
		if (meal + ((unsigned long long)input->die / 1000) < get_time(input))
		{
			printf("%llu %d dies\n", get_time(input), input->num);
			break ;
		}
		printf("%llu %d eats\n", get_time(input), input->num);
		usleep(input->eat);
		meal = get_time(input);
		printf("%llu %d sleeps\n", get_time(input), input->num);
		usleep(input->sleep);
		i++;
	}
	return ((void *)input);
}

t_philo	fill_struct_philo(t_info_i input)
{
	t_philo	philos;

	philos.start_time = start_time();
	philos.must_eat = input.must_eat;
	philos.eat = input.eat;
	philos.die = input.die;
	philos.sleep = input.sleep;
	return (philos);
}

int	philo(t_info_i input)
{
	int		i;
	t_philo	*philos;

	philos = ft_calloc(sizeof(t_philo), input.count);
	input.philos = ft_calloc(sizeof(pthread_t), input.count);
	input.forks = ft_calloc(sizeof(pthread_mutex_t), input.count);
	i = 0;
	while (i < (int)input.count)
	{
		printf("Philosopher: %d\n", i + 1);
		pthread_mutex_init(&(input.forks[i]), NULL);
		philos[i] = fill_struct_philo(input);
		philos[i].num = i + 1;
		pthread_create(&(input.philos[i]), NULL, (t_thread_func)threading, (void *)&philos[i]);
		i++;
	}
	pthread_join(input.philos[i - 1], NULL);
	return (0);
}

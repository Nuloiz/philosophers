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

static int	eat(t_philo *input, unsigned long long meal)
{
	pthread_mutex_lock((input->l_fork));
	pthread_mutex_lock((input->r_fork));
	if (meal + ((unsigned long long)input->die / 1000) < get_time(input))
	{
		printf("%llu %d dies\n", get_time(input), input->num);
		pthread_mutex_unlock((input->l_fork));
		pthread_mutex_unlock((input->r_fork));
		return (-1);
	}
	printf("%llu %d eats\n", get_time(input), input->num);
	usleep(input->eat);
	pthread_mutex_unlock((input->l_fork));
	pthread_mutex_unlock((input->r_fork));
	return (0);
}

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
		if (eat(input, meal) == -1)
			break;
		meal = get_time(input);
		if (meal + ((unsigned long long)input->die / 1000) < get_time(input))
		{
			printf("%llu %d dies\n", get_time(input), input->num);
			break ;
		}
		printf("%llu %d sleeps\n", get_time(input), input->num);
		usleep(input->sleep);
		i++;
	}
	return ((void *)input);
}

static t_philo	fill_struct_philo(t_info_i input)
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
	i = -1;
	while (++i < input.count)
		pthread_mutex_init(&(input.forks[i]), NULL);
	i = 0;
	while (i < input.count)
	{
		philos[i] = fill_struct_philo(input);
		philos[i].num = i + 1;
		philos[i].r_fork = &input.forks[i];
		if (i == 0)
			philos[i].l_fork = &input.forks[input.count - 1];
		else
			philos[i].l_fork = &input.forks[i - 1];
		pthread_create(&(input.philos[i]), NULL, (t_thread_func)threading, (void *)&philos[i]);
		i++;
	}
	pthread_join(input.philos[i - 1], NULL);
	free_every(philos, input);
	return (0);
}

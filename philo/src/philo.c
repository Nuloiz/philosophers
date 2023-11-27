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
	if (input->kill == 1)
		return (-1);
	if (meal + ((unsigned long long)input->die / 1000) < get_time(input))
	{
		printf("%llu %d died\n", get_time(input), input->num);
		input->alive = 0;
		pthread_mutex_unlock((input->l_fork));
		return (-1);
	}
	pthread_mutex_lock((input->r_fork));
	if (input->kill == 1)
		return (-1);
	if (meal + ((unsigned long long)input->die / 1000) < get_time(input))
	{
		printf("%llu %d died\n", get_time(input), input->num);
		input->alive = 0;
		pthread_mutex_unlock((input->l_fork));
		pthread_mutex_unlock((input->r_fork));
		return (-1);
	}
	printf("%llu %d is eating\n", get_time(input), input->num);
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
		if (input->must_eat == i || input->kill == 1)
			break ;
		if (eat(input, meal) == -1)
			break ;
		meal = get_time(input);
		if (meal + ((unsigned long long)input->die / 1000) < get_time(input))
		{
			printf("%llu %d died\n", get_time(input), input->num);
			input->alive = 0;
			break ;
		}
		printf("%llu %d is sleeping\n", get_time(input), input->num);
		usleep(input->sleep);
		i++;
	}
	input->fed_up = 1;
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
	philos.alive = 1;
	philos.fed_up = 0;
	philos.kill = 0;
	return (philos);
}

void	philos_fed_up(t_info_i *input)
{
	int	i;
	int j;

	i = 0;
	j = 1;
	while (i < input->count)
	{
		if (input->philos[i].fed_up == 0)
		{
			j = 0;
			break ;
		}
		i++;
	}
	input->all_fed_up = j;
}

int	philo(t_info_i input)
{
	int		i;

	input.philos = ft_calloc(sizeof(t_philo), input.count);
	input.thread = ft_calloc(sizeof(pthread_t), input.count);
	input.forks = ft_calloc(sizeof(pthread_mutex_t), input.count);
	i = -1;
	while (++i < input.count)
		pthread_mutex_init(&(input.forks[i]), NULL);
	i = 0;
	while (i < input.count)
	{
		input.philos[i] = fill_struct_philo(input);
		input.philos[i].num = i + 1;
		input.philos[i].r_fork = &input.forks[i];
		if (i == 0)
			input.philos[i].l_fork = &input.forks[input.count - 1];
		else
			input.philos[i].l_fork = &input.forks[i - 1];
		pthread_create(&(input.thread[i]), NULL, (t_thread_func)threading, (void *)&(input.philos[i]));
		i++;
	}
	while (1)
	{
		i = -1;
		while (++i < input.count)
		{
			philos_fed_up(&input);
			if (input.all_fed_up)
				return (free_every(input), -1);
			else if (input.philos[i].alive == 0)
				return (someone_died(&input), -1);
		}
	}
}

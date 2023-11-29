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

static void	take_forks(t_philo *input)
{
	if (input->num % 2 == 0)
	{
		pthread_mutex_lock((input->l_fork));
		prot_print("has taken a fork", input);
		pthread_mutex_lock((input->r_fork));
		prot_print("has taken a fork", input);
	}
	else
	{
		pthread_mutex_lock((input->r_fork));
		prot_print("has taken a fork", input);
		pthread_mutex_lock((input->l_fork));
		prot_print("has taken a fork", input);
	}
}

static void	eat(t_philo *input)
{
	take_forks(input);
	input->meal = get_time(input);
	prot_print("is eating", input);
	own_sleep(input->eat, input);
	if (input->num % 2 == 0)
	{
		pthread_mutex_unlock((input->l_fork));
		pthread_mutex_unlock((input->r_fork));
	}
	else
	{
		pthread_mutex_unlock((input->r_fork));
		pthread_mutex_unlock((input->l_fork));
	}
}

static void	*threading(t_philo *input)
{
	int					i;

	i = 0;
	while (1)
	{
		if (input->must_eat == i)
			input->fed_up = 1;
		eat(input);
		if (!prot_print("is sleeping", input))
			break ;
		own_sleep(input->sleep, input);
		if (!prot_print("is thinking", input))
			break ;
		i++;
	}
	return ((void *)input);
}

static t_philo	fill_struct_philo(t_info_i *input)
{
	t_philo	philos;

	philos.start_time = start_time();
	philos.must_eat = input->must_eat;
	philos.eat = input->eat;
	philos.die = input->die;
	philos.sleep = input->sleep;
	philos.meal = 0;
	philos.fed_up = 0;
	philos.print_m = &input->print_m;
	philos.print_b = &input->print_b;
	philos.print_bm = &input->print_bm;
	return (philos);
}

static int	philos_fed_up(t_info_i *input)
{
	int	i;

	i = 0;
	while (i < input->count)
	{
		if (input->philos[i].fed_up == 0)
			return (1);
		i++;
	}
	pthread_mutex_lock(&(input->print_bm));
	input->print_b = 0;
	pthread_mutex_unlock(&(input->print_bm));
	free_every(*input);
	return (0);
}

int	philo(t_info_i input)
{
	int		i;

	input.philos = ft_calloc(sizeof(t_philo), input.count);
	input.thread = ft_calloc(sizeof(pthread_t), input.count);
	input.forks = ft_calloc(sizeof(pthread_mutex_t), input.count);
	pthread_mutex_init(&(input.print_m), NULL);
	input.print_b = 1;
	pthread_mutex_init(&(input.print_bm), NULL);
	i = -1;
	while (++i < input.count)
		pthread_mutex_init(&(input.forks[i]), NULL);
	i = 0;
	while (i < input.count)
	{
		input.philos[i] = fill_struct_philo(&input);
		input.philos[i].num = i + 1;
		input.philos[i].r_fork = &input.forks[i];
		if (i == 0)
			input.philos[i].l_fork = &input.forks[input.count - 1];
		else
			input.philos[i].l_fork = &input.forks[i - 1];
		pthread_create(&(input.thread[i]), NULL, (t_thread_func)threading, \
						(void *)&(input.philos[i]));
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < input.count)
		{
			if (!philos_fed_up(&input))
				return (0);
			if (input.philos[i].meal + ((unsigned long long)input.philos[i].die \
				/ 1000) < get_time((&input.philos[i])))
			{
				prot_print("died", &(input.philos[i]));
				pthread_mutex_lock(&(input.print_bm));
				input.print_b = 0;
				pthread_mutex_unlock(&(input.print_bm));
				return (free_every(input), -1);
			}
			i++;
		}
	}
}

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

static int	check_philos(t_info_i *input)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < input->count)
		{
			if (!philos_fed_up(input))
				return (0);
			if (input->philos[i].meal + ((unsigned long long) \
			input->philos[i].die / 1000) < get_time((&input->philos[i])))
			{
				prot_print("died", &(input->philos[i]));
				pthread_mutex_lock(&(input->print_bm));
				input->print_b = 0;
				pthread_mutex_unlock(&(input->print_bm));
				return (free_every(*input), -1);
			}
			i++;
		}
	}
}

static void	one_philo(t_info_i *input)
{
	pthread_mutex_lock(&(input->forks[0]));
	printf("0 1 has taken a fork");
	sleep(input->die + 200000);
	pthread_mutex_unlock(&(input->forks[0]));
	
}

int	philo(t_info_i input)
{
	int		i;

	fill_struct_info(&input);
	i = -1;
	while (++i < input.count)
		pthread_mutex_init(&(input.forks[i]), NULL);
	i = 0;
	if (input.count == 1)
		return (one_philo(&input), 1);
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
	return (check_philos(&input));
}

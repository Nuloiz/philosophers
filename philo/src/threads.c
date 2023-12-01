/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:30:29 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/29 15:30:29 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock((input->meal_m));
	input->meal = get_time(input);
	pthread_mutex_unlock((input->meal_m));
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

void	*threading(t_philo *input)
{
	int					i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock((input->fed_up_m));
		if (input->must_eat == i)
			input->fed_up = 1;
		pthread_mutex_unlock((input->fed_up_m));
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

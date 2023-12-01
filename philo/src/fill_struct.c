/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:12:40 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/30 10:12:40 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_struct_info(t_info_i *input)
{
	int	i;

	i = -1;
	input->philos = ft_calloc(sizeof(t_philo), input->count);
	input->thread = ft_calloc(sizeof(pthread_t), input->count);
	input->forks = ft_calloc(sizeof(pthread_mutex_t), input->count);
	input->meals = ft_calloc(sizeof(pthread_mutex_t), input->count);
	pthread_mutex_init(&(input->print_m), NULL);
	input->print_b = 1;
	pthread_mutex_init(&(input->print_bm), NULL);
	while (++i < input->count)
	{
		pthread_mutex_init(&(input->forks[i]), NULL);
		pthread_mutex_init(&(input->meals[i]), NULL);
	}
}

t_philo	fill_struct_philo(t_info_i *input)
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

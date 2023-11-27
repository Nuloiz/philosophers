/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prot_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:56:46 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/27 14:56:46 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prot_print(char *str, t_philo *input)
{
	pthread_mutex_lock(input->print_m);
	if (*input->print_b == 0)
		return (pthread_mutex_unlock(input->print_m), -1);
	printf("%llu %d %s\n", get_time(input), input->num, str);
	pthread_mutex_unlock(input->print_m);
	return (1);
}

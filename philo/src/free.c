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

void	free_every(t_philo *philos, t_info_i input)
{
	free(philos);
	free(input.philos);
	free(input.forks);
}

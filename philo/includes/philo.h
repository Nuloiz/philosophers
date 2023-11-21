/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:09:30 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/21 09:09:30 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FUN "/bin/rm"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <pthread.h>

typedef struct s_info_i
{
	long	count;
	long	die;
	long	eat;
	long	sleep;
}	t_info_i;

int		main(int argc, char **argv);
long	ft_atoi(const char *str);

#endif
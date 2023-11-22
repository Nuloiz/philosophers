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
# include <sys/time.h>

typedef struct s_info_i
{
	long				count;
	long				die;
	long				eat;
	long				sleep;
	long				must_eat;
	pthread_mutex_t		*fork;
	unsigned long long	start_time;
}	t_info_i;

int					main(int argc, char **argv);
int					philo(t_info_i input);
unsigned long long	get_time(t_info_i *input);
unsigned long long	start_time(void);
long				ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);

#endif
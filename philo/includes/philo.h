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

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
	unsigned long		die;
	unsigned long		eat;
	unsigned long		sleep;
	int					must_eat;
	int					num;
	unsigned long long	start_time;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	unsigned long long	meal;
	int 				fed_up;
	pthread_mutex_t		*print_m;
	int 				*print_b;

}	t_philo;

typedef struct s_info_i
{
	int					count;
	unsigned long		die;
	unsigned long		eat;
	unsigned long		sleep;
	int					must_eat;
	pthread_mutex_t		*forks;
	pthread_t			*thread;
	t_philo				*philos;
	int 				all_fed_up;
	pthread_mutex_t		print_m;
	int 				print_b;
}	t_info_i;

int					main(int argc, char **argv);
int					philo(t_info_i input);
unsigned long long	get_time(t_philo *input);
unsigned long long	start_time(void);
int					prot_print(char *str, t_philo *input);
void				free_every(t_info_i input);
long				ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);

#endif
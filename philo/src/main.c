/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:09:08 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/21 09:09:08 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
	{
		return (0);
	}
	return (1);
}

static int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 4)
		return (printf("Error: To less arguments\n"));
	else if (argc > 5)
		return (printf("Error: To many arguments\n"));
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (printf("Error: Arguments are non numeric\n"));
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info_i	input;

	argc--;
	argv++;
	if (check_input(argc, argv) > 1)
		return (0);
	printf("test");
	input.count = ft_atoi(argv[0]);
	input.die = ft_atoi(argv[1]) * 1000;
	input.eat = ft_atoi(argv[2]) * 1000;
	input.sleep = ft_atoi(argv[3]) * 1000;
	printf("test");
	if (argc == 5)
		input.must_eat = ft_atoi(argv[4]);
	else
		input.must_eat = -1;
	printf("test");
	return (philo(input));
}

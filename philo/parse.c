/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:45:49 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:45:53 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

long	ft_atol(char *str)
{
	long	result;
	int		i;
	int		digit;

	result = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		digit = str[i] - '0';
		if (result > (MAX_INT - digit) / 10)
			return (-1);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

int	is_valid_number(char *str)
{
	int		i;
	long	value;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	value = ft_atol(str);
	if (value <= 0 || value > MAX_INT)
		return (0);
	return (1);
}

static int	check_all_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (print_error());
	if (!check_all_args(argc, argv))
		return (print_error());
	table->number_of_philos = (int)ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->has_must_eat = 0;
	table->must_eat = -1;
	if (argc == 6)
	{
		table->has_must_eat = 1;
		table->must_eat = (int)ft_atol(argv[5]);
	}
	table->start_time = 0;
	table->simulation_end = 0;
	table->forks = NULL;
	table->philos = NULL;
	return (0);
}

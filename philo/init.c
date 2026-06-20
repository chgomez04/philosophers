/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:40:02 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:40:08 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->number_of_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->number_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_forks(table, i);
			free(table->forks);
			table->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->end_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_mutex);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	if (init_forks(table) != 0)
		return (1);
	if (init_table_mutexes(table) != 0)
	{
		destroy_forks(table, table->number_of_philos);
		free(table->forks);
		table->forks = NULL;
		return (1);
	}
	return (0);
}

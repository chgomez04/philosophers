/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:40:36 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:40:39 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_table *table, int i)
{
	table->philos[i].left_fork = &table->forks[i];
	table->philos[i].right_fork = &table->forks[(i + 1)
		% table->number_of_philos];
}

static void	init_one_philo(t_table *table, int i)
{
	table->philos[i].id = i + 1;
	table->philos[i].meals_eaten = 0;
	table->philos[i].last_meal_time = 0;
	table->philos[i].table = table;
	assign_forks(table, i);
}

static void	destroy_philo_mutexes(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
}

int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->number_of_philos);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < table->number_of_philos)
	{
		init_one_philo(table, i);
		if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0)
		{
			destroy_philo_mutexes(table, i);
			free(table->philos);
			table->philos = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

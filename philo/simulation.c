/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:48:34 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:49:14 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

static int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
		{
			set_simulation_end(table);
			join_threads(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_table *table)
{
	table->start_time = get_time_ms();
	if (create_threads(table) != 0)
		return (1);
	monitor(table);
	join_threads(table, table->number_of_philos);
	return (0);
}

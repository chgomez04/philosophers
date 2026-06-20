/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:45:20 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:45:26 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_philo_died(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_time_ms() - philo->last_meal_time > philo->table->time_to_die + 8)
	{
		dead = 1;
		set_simulation_end(philo->table);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	if (dead)
	{
		print_death(philo);
		return (1);
	}
	return (0);
}

static int	all_philos_ate(t_table *table)
{
	int	i;
	int	count;

	if (!table->has_must_eat)
		return (0);
	i = 0;
	count = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meals_eaten >= table->must_eat)
			count++;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (count == table->number_of_philos);
}

void	monitor(t_table *table)
{
	int	i;

	while (!is_simulation_end(table))
	{
		i = 0;
		while (i < table->number_of_philos)
		{
			if (has_philo_died(&table->philos[i]))
				return ;
			i++;
		}
		if (all_philos_ate(table))
		{
			set_simulation_end(table);
			return ;
		}
		usleep(300);
	}
}

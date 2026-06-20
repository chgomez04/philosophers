/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:39:18 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:39:33 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_philos(t_table *table)
{
	int	i;

	if (!table->philos)
		return ;
	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	free(table->philos);
	table->philos = NULL;
}

static void	clean_forks(t_table *table)
{
	int	i;

	if (!table->forks)
		return ;
	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
}

void	clean_all(t_table *table)
{
	clean_philos(table);
	clean_forks(table);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->end_mutex);
}

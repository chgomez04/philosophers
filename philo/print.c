/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:47:02 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:47:08 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (!is_simulation_end(table))
	{
		printf("%ld %d %s\n",
			get_timestamp(table), philo->id, status);
	}
	pthread_mutex_unlock(&table->print_mutex);
}

void	print_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d died\n", get_timestamp(table), philo->id);
	pthread_mutex_unlock(&table->print_mutex);
}

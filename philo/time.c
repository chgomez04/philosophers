/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:49:36 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:49:40 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_timestamp(t_table *table)
{
	return (get_time_ms() - table->start_time);
}

int	is_simulation_end(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->end_mutex);
	result = table->simulation_end;
	pthread_mutex_unlock(&table->end_mutex);
	return (result);
}

void	set_simulation_end(t_table *table)
{
	pthread_mutex_lock(&table->end_mutex);
	table->simulation_end = 1;
	pthread_mutex_unlock(&table->end_mutex);
}

void	precise_sleep(long time_ms, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time_ms();
	while (!is_simulation_end(table))
	{
		elapsed = get_time_ms() - start;
		if (elapsed >= time_ms)
			break ;
		remaining = time_ms - elapsed;
		if (remaining > 10)
			usleep((remaining - 5) * 1000);
		else
			usleep(100);
	}
}

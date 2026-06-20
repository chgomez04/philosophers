/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:43:58 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:44:02 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse_args(argc, argv, &table) != 0)
		return (1);
	if (init_mutexes(&table) != 0)
		return (1);
	if (init_philos(&table) != 0)
	{
		clean_all(&table);
		return (1);
	}
	if (start_simulation(&table) != 0)
	{
		clean_all(&table);
		return (1);
	}
	clean_all(&table);
	return (0);
}

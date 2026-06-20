/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 11:46:33 by chgomez           #+#    #+#             */
/*   Updated: 2026/05/24 11:46:37 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_INT 2147483647

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				has_must_eat;
	long			start_time;
	int				simulation_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	t_philo			*philos;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

/* Parse */
int		parse_args(int argc, char **argv, t_table *table);
long	ft_atol(char *str);
int		is_valid_number(char *str);

/* Init */
int		init_mutexes(t_table *table);
int		init_philos(t_table *table);

/* Clean */
void	clean_all(t_table *table);

/* Time */
long	get_time_ms(void);
long	get_timestamp(t_table *table);
void	precise_sleep(long time_ms, t_table *table);

/* State */
int		is_simulation_end(t_table *table);
void	set_simulation_end(t_table *table);

/* Print */
void	print_status(t_philo *philo, char *status);
void	print_death(t_philo *philo);

/* Routine */
int		start_simulation(t_table *table);
void	*philo_routine(void *arg);
void	think(t_philo *philo);

/* Monitor */
void	monitor(t_table *table);
#endif

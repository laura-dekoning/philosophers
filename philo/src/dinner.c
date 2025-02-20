/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/20 12:25:23 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	single_philo(t_table *table)
{
	pthread_mutex_lock(&table->prog_m[DISPLAY]);
	printf("%-6i%d %s\n", 0, 1, FORK);
	precise_usleep(table->time_to_die, table);
	printf("%-6ld%d %s\n", table->time_to_die, 1, DIED);
	pthread_mutex_unlock(&table->prog_m[DISPLAY]);
	return (ERROR);
}

void	need_to_eat(t_philo *philo)
{
	size_t	time_gap;
	size_t	time_die;
	size_t	time_eat;
	size_t	enough_time;

	pthread_mutex_lock(&philo->meal_time_m);
	if (philo->last_meal_time != 0)
	{
		time_gap = gettime() - philo->last_meal_time;
		time_die = philo->table->time_to_die;
		time_eat = philo->table->time_to_eat;
		enough_time = (time_die - time_eat);
		if (time_gap < enough_time)
			precise_usleep(time_eat, philo->table);
		pthread_mutex_unlock(&philo->meal_time_m);
	}
	else
		pthread_mutex_unlock(&philo->meal_time_m);
}

/**
 * Dinner routine
 * ----------------------------------------------------------
 * 1) All philos have to wait till ready --> ready_to_start
 * 2) Endless philo loop till philos full or died
 * 3) Odd philos start with a small wait
 */
void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->prog_m[START]);
	pthread_mutex_unlock(&philo->table->prog_m[START]);
	if (philo->philo_id % 2 == 0)
		precise_usleep((philo->table->time_to_eat / 2), philo->table);
	while (!simulation_finished(philo->table))
	{
		need_to_eat(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	dinner_start(t_table *table)
{
	if (table->meal_limit == 0)
		return (SUCCESS);
	else if (table->philo_count == 1)
		return (single_philo(table));
	if (create_threads(table) == ERROR)
		return (ERROR);
	monitor(table);
	join_threads(table, table->philo_count);
	return (SUCCESS);
}
// dinner routine start ff iets sneller skrrr maken bro
// als iemand starving is, pech, die moet DOOOODDDDDD!!!!!

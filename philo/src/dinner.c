/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/13 15:06:35 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	single_philo(t_table *table)
{
	pthread_mutex_lock(&table->prog_m[DISPLAY]);
	printf("%-6i%d %s\n", 0, 1, FORK);
	precise_usleep(table->time_to_die);
	printf("%-6ld%d %s\n", table->time_to_die, 1, DIED);
	pthread_mutex_unlock(&table->prog_m[DISPLAY]);
	return (ERROR);
}

/**
 * Dinner routine
 * ----------------------------------------------------------
 * 1) All philos have to wait till ready --> ready_to_start
 * 2) Endless philo loop till philos full or died
 * 3) Odd philos start with sleeping
 */
void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->prog_m[START]);
	pthread_mutex_unlock(&philo->table->prog_m[START]);
	if (philo->philo_id % 2)
		precise_usleep(philo->table->time_to_eat / 2);
	while (!simulation_finished(philo->table))
	{
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
	table->start_simulation = gettime();
	monitor(table);
	join_threads(table, table->philo_count);
	return (SUCCESS);
}
// dinner routine start ff iets sneller skrrr maken bro
// als iemand starving is, pech, die moet DOOOODDDDDD!!!!!

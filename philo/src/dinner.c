/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/12 11:39:11 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (get_bool(&philo->table->prog_m[START], &philo->table->ready_to_start) != true)
		waiting(philo);
	if (philo->philo_id % 2 == 0)
		waiting(philo);
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
	if (table->meal_limit == 0 || table->philo_count == 1)
		return (SUCCESS);
	if (create_threads(table) == ERROR)
		return (ERROR);
	table->start_simulation = gettime();
	set_bool(&table->table_mutex, &table->ready_to_start, true);
	monitor(table);
	join_threads(table, table->philo_count);
	return (SUCCESS);
}


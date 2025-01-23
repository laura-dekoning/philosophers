/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/23 16:01:30 by lade-kon      ########   odam.nl         */
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
	if (get_bool(&philo->table->prog_m[START], &philo->table->ready_to_start) == true)
	{
		if (philo->philo_id % 2 == 0)
			waiting(philo);
		while (!simulation_finished(philo->table))
		{
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}

int	create_philo_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo_threads[i], NULL,
				&dinner_routine, &table->philos[i]) != SUCCESS)
		{
			while (i > 0)
			{
				i--;
				pthread_join(table->philo_threads[i], NULL);
			}
			return (ft_error(table, PHILO));
		}
		i++;
	}
	return (SUCCESS);
}

int	dinner_start(t_table *table)
{
	size_t	i;

	if (table->meal_limit == 0 || table->philo_count == 1)
		return (SUCCESS);
	if (create_philo_threads(table) == ERROR)
		return (ERROR);
	set_size_t(&table->table_mutex, &table->start_simulation, gettime());
	set_bool(&table->table_mutex, &table->ready_to_start, true);
	monitor_routine(table);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philo_threads[i], NULL);
		i++;
	}
	return (SUCCESS);
}

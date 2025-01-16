/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/16 17:22:17 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



static void	*monitor_routine(void *data)
{
	t_table	*table;
	size_t	time;
	size_t	i;

	table = (t_table *)data;
	while (table->end_simulation == false)
	{
		i = 0;
		while (i < table->philo_count)
		{
			mutex_handle(&table->philos[i].philo_mutex, LOCK);
			mutex_handle(&table->time_mutex, LOCK);
			time = gettime(MILLISECONDS);
			if (is_philo_dead(table, time, i) == true)
				set_bool(&table->write_mutex, &table->end_simulation, true);
			mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
			mutex_handle(&table->time_mutex, UNLOCK);
			i++;
		}
		if (all_philos_full(table) == true)
			set_bool(&table->write_mutex, &table->end_simulation, true);
	}
	return (NULL);
}

/**
 * Dinner routine
 * ----------------------------------------------------------
 * 1) All philos have to wait till ready --> wait_all_threads
 * 2) Endless philo loop till philos full or died
 * 3) Odd philos start with sleeping
 */
void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	if (philo->philo_id % 2 == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	else
		sleeping(philo);
	while (!simulation_finished(philo->table))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	create_philo_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo_threads[i], NULL, dinner_routine, &table->philos[i]) != SUCCESS)
		{
			while (i > 0)
			{
				i--;
				pthread_join(table->philo_threads[i], NULL);
			}
			return (ft_error(table, "Something went wrong will creating philo threads"));
		}
		i++;
	}
	return (SUCCESS);
}

int	create_monitor_thread(t_table *table)
{
	size_t	i;

	if (pthread_create(table->monitor_thread, NULL, monitor_routine, table) == ERROR)
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_join(table->philo_threads[i], NULL);
			i++;
		}
		pthread_join(*table->monitor_thread, NULL);
		return (ft_error(table, "Something went wrong will creating the monitoring thread"));
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
	if (create_monitor_thread(table) == ERROR)
		return (ERROR);
	gettimeofday(&table->start_time, NULL);
	table->start_simulation = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philo_threads[i], NULL);
		i++;
	}
	pthread_join(*table->monitor_thread, NULL);
	return (SUCCESS);
}

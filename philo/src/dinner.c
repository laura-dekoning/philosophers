/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/16 16:59:15 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	all_philos_full(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		mutex_handle(&table->philos[i].philo_mutex, LOCK);
		if (table->philos[i].full == false)
		{
			mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
			return (false);
		}
		mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
		i++;
	}
	return (true);
}

static bool	is_philo_dead(t_table *table, size_t time, size_t i)
{
	if (table->philos[i].last_meal_time == 0)
	{
		if ((time - table->start_simulation) > table->time_to_die)
		{
			write_status(DEAD, &table->philos[i]);
			return (true);
		}
	}
	else
	{
		if ((time - table->philos[i].last_meal_time) > table->time_to_die)
		{
			write_status(DEAD, &table->philos[i]);
			return (true);
		}
	}
	return (false);
}

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

int	dinner_start(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->meal_limit == 0 || table->philo_count == 1)
		return (SUCCESS);
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo_threads[i], NULL, dinner_routine, &table->philos[i]) != SUCCESS)
		{
			while (i > 0)
			{
				i--;
				pthread_join(table->philo_threads[i], NULL);
			}
			return (ft_error(table, "Threading"));
		}
		i++;
	}
	if (pthread_create(table->monitor_thread, NULL, monitor_routine, table) != SUCCESS)
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_join(table->philo_threads[i], NULL);
			i++;
		}
		pthread_join(*table->monitor_thread, NULL);
		return (ft_error(table, "Monitoring Threading"));
	}
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

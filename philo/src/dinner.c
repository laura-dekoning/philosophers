/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/09 17:09:34 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
	usleep(600);
}

static void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

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

/**
 * eat routine
 * 1) grab forks
 * 2) eating : write eat, update last meal, update meals counter, 
 * 	  eventually bool full
 * 3) release forks
 */
static void	eating(t_philo *philo)
{
	mutex_handle(philo->first_fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handle(philo->second_fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECONDS));
	philo->meals_eaten++;
	write_status(EATING, philo);
	// printf(B_O"Philo[%i] -> meals eaten: %li\n"DEF, philo->philo_id ,philo->meals_eaten);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meal_limit > 0
		&& philo->meals_eaten == philo->table->meal_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(philo->first_fork, UNLOCK);
	mutex_handle(philo->second_fork, UNLOCK);
}

/**
 * 1) All philos have to wait till ready, synchro start
 * 
 * 2) Endless philo loop
 */
void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	// 2.0) odd philos start with sleeping so not everyone starts with trying to get the fork
	if (philo->philo_id % 2 == 0)
	{
		// printf(B_Y"philo[%i] is even\n"DEF, philo->philo_id);
		eating(philo);
	}
	else
		sleeping(philo);
	while (!simulation_finished(philo->table))
	{
		// 1) am i full?
		if (all_philos_full(philo->table))//TODO thread safe if all philos are full
			break ;
		// 2) eat
		eating(philo);
		// 3) sleep --> write status & precise usleep
		sleeping(philo);
		// 4) think
		thinking(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *data)
{
	t_table	*table;
	size_t	time;
	size_t	i;

	table = (t_table *)data;
	while (table->death == false) //THIS makes sure the monitoring will go on
	{
		i = 0;
		while (i < table->philo_count)
		{
			mutex_handle(&table->philos[i].philo_mutex, LOCK);
			mutex_handle(&table->time_mutex, LOCK);
			time = gettime(MILLISECONDS);
			if (table->philos[i].last_meal_time == 0)
			{
				if ((time - table->start_simulation) > table->time_to_die)
				{
					set_bool(&table->write_mutex, &table->death, true);
					printf("Time: %li	Last meal time philo[%li]: %li\n", time, i + 1, table->philos[i].last_meal_time);
					printf(B_G"Philo[%li]: Time since last meal: %li\n"DEF, i + 1, (time - table->philos[i].last_meal_time));
					printf(B_R"philo[%li] died\n"DEF, (i+1));
					//MAKE SURE THE PROGRAM CLEANS AND STOPS.
					return (NULL);
				}
			}
			else
			{
				if ((time - table->philos[i].last_meal_time) > table->time_to_die)
				{
					set_bool(&table->write_mutex, &table->death, true);
					printf("Time: %li	Last meal time philo[%li]: %li\n", time, i + 1, table->philos[i].last_meal_time);
					printf(B_G"Philo[%li]: Time since last meal: %li\n"DEF, i + 1, (time - table->philos[i].last_meal_time));
					printf(B_R"philo[%li] died\n"DEF, (i+1));
					//MAKE SURE THE PROGRAM CLEANS AND STOPS.
					return (NULL);
				}
			}
			mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
			mutex_handle(&table->time_mutex, UNLOCK);
			i++;
		}
		if (all_philos_full(table) == true)
			return (NULL);
	}
	return (NULL);
}

int	dinner_start(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->meal_limit == 0 || table->philo_count == 1)
		return (SUCCESS); // back to main, clean 
	// Create philosopher threads
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo_threads[i], NULL, dinner_routine, &table->philos[i]) != SUCCESS)
		{
			// Cleanup in case of failure
			while (i > 0)
			{
				i--;
				pthread_join(table->philo_threads[i], NULL);
			}
			return (ft_error(table, "Threading"));
		}
		i++;
	}

	// Start monitoring thread
	if (pthread_create(table->monitor_thread, NULL, monitor_routine, table) != SUCCESS)
	{
		// Cleanup in case of failure
		i = 0;
		while (i < table->philo_count)
		{
			pthread_join(table->philo_threads[i], NULL);
			i++;
		}
		pthread_join(*table->monitor_thread, NULL);
		return (ft_error(table, "Monitoring Threading"));
	}

	// Record start time and signal all threads to proceed
	gettimeofday(&table->start_time, NULL);
	table->start_simulation = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	// Wait for all philosopher threads to finish
	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philo_threads[i], NULL);
		i++;
	}

	// Wait for the monitoring thread to finish
	pthread_join(*table->monitor_thread, NULL);

	// If we get here, all philosophers are either full or dead
	return (SUCCESS);
}

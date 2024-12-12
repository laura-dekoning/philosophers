/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/12/12 21:03:53 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	write_status(THINKING, philo);
}

/**
 * eat routine
 * 1) grab forks
 * 2) eating : write eat, update last meal, update meals counter, 
 * 	  eventually bool full
 * 3) release forks
 */
static void	eat(t_philo *philo)
{
	mutex_handle(philo->first_fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handle(philo->second_fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECONDS));
	philo->meals_eaten++;
	write_status(EATING, philo);
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
	// set last meal time

	while (!simulation_finished(philo->table))
	{
		// 1) am i full?
		if (philo->full)//TODO thread safe
			break ;
		// 2) eat
		eat(philo);
		// 3) sleep --> write status & precise usleep
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);

		// 4) think
		think(philo);
	}
	return (NULL);
}

int	dinner_start(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->meal_limit == 0)
		return (SUCCESS); //back to main, clean
	else if (table->philo_count == 1)
		return (SUCCESS); 
	else
	{
		while (i < table->philo_count)
		{
			if (pthread_create(&table->philo_threads[i], 0, dinner_routine, &table->philos[i]) != SUCCESS)
			{
				while (i >= 0)
				{
					pthread_join(table->philo_threads[i], NULL);
					i--;
				}
				return (ft_error(table, "Threading"));
			}
			i++;
		}
	}
	gettimeofday(&table->start_time, NULL);
	table->start_simulation = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//wait for everyone
	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philo_threads[i], NULL);
		i++;
	}
	// if we get here, all philos are full!
	return (SUCCESS);
}






/**
 * THIS IS THE CHATGPT EXAMPLE
 * JUST WANTED TO READ BACK*/
int	dinner_start(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->meal_limit == 0)
		return (SUCCESS); // back to main, clean
	else if (table->philo_count == 1)
		return (SUCCESS); 

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
	if (pthread_create(&table->monitor_thread, NULL, monitor_philos, table) != SUCCESS)
	{
		// Cleanup in case of failure
		i = 0;
		while (i < table->philo_count)
		{
			pthread_join(table->philo_threads[i], NULL);
			i++;
		}
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
	pthread_join(table->monitor_thread, NULL);

	// If we get here, all philosophers are either full or dead
	return (SUCCESS);
}

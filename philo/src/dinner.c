/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/14 14:12:51 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
		precise_usleep(philo);

		// 4) think
		thinking(philo);
	}
	return (NULL);
}

int	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->meal_limit == 0)
		return (SUCCESS); //back to main, clean
	else if (table->philo_count == 1)
		;//TODO 
	else
	{
		while (i < table->philo_count)
		{
			if (pthread_create(table->philo_threads[i], 0, dinner_routine, &table->philos[i]) != SUCCESS)
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
		pthread_join(&table->philos[i], NULL);
		i++;
	}
	// if we get here, all philos are full!
}

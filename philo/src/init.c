/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:48:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/22 13:03:21 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Every philosopher starts with his own fork on the right side.
 * So philo[0] (philo 1) has fork[0] on the right and fork[philo_count]
 * on the right side. 
 */
void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	int	nbr_philos;

	nbr_philos = philo->table->philo_count;
	if (i == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[nbr_philos - 1];
	}
	else if (i % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i - 1) % nbr_philos];
	}
	else
	{
		philo->first_fork = &forks[(i - 1) % nbr_philos];
		philo->second_fork = &forks[i];
	}
}

int	malloc_data(t_table *table)
{
	table->philos = (t_philo *)malloc(sizeof(t_philo)
			* table->philo_count);
	if (!table->philos)
		return (ft_error(table, MALLOC));
	table->philo_threads = (pthread_t *)malloc(sizeof(pthread_t)
			* table->philo_count);
	if (!table->philo_threads)
		return (ft_error(table, MALLOC));
	table->monitor_thread = (pthread_t *)malloc(sizeof(pthread_t)
			* table->philo_count);
	if (!table->monitor_thread)
		return (ft_error(table, MALLOC));
	return (SUCCESS);
}

int	init_philos(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	if (malloc_data(table) != SUCCESS)
		return (ERROR);
	i = 0;
	while (i < table->philo_count)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal_time = 0;
		philo->full = false;
		philo->table = table;
		assign_forks(philo, table->forks, i);
		if (mutex_handle(&philo->philo_mutex, INIT) != SUCCESS)
			return (ft_error(table, MUTEX_INIT));
		i++;
	}
	return (SUCCESS);
}

int	init_table(t_table *table)
{
	int	retval;

	retval = 0;
	table->end_simulation = false;
	table->ready_to_start = false;
	table->eat_limit = false;
	if (init_mutexes(table) != SUCCESS)
		return (ft_error(table, MUTEX_INIT));
	retval = init_philos(table);
	if ((unsigned long)retval != table->philo_count)
	{
		while (retval > 0)
		{
			if (pthread_join(table->philo_threads[retval], NULL) != SUCCESS)
				return (ft_error(table, THREAD_JOIN));
			retval--;
		}
	}
	//CHECK IF THIS ABOVE IS NECESSARY
	return (SUCCESS);
}

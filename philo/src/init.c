/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:48:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/19 14:06:01 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Every philosopher starts with his own fork on the right side.
 * So philo[0] (philo 1) has fork[0] on the right and fork[philo_count]
 * on the left side. 
 */
void	assign_forks(t_table *table, pthread_mutex_t *forks)
{
	int	nbr_philos;
	int	i;

	i = 0;
	nbr_philos = table->philo_count;
	while (i < nbr_philos)
	{
		if (i % 2 == 0) // Even philosophers
		{
			table->philos[i].first_fork = &forks[i];
			table->philos[i].second_fork = &forks[(i + 1) % nbr_philos]; // Next fork cyclically
		}
		else // Odd philosophers
		{
			table->philos[i].first_fork = &forks[(i + 1) % nbr_philos]; // Next fork cyclically
			table->philos[i].second_fork = &forks[i];
		}
		// table->philos[i].first_fork = &forks[i];
		// if (i == 0)
		// {
		// 	table->philos[i].first_fork = &forks[nbr_philos - 1];
		// 	table->philos[i].second_fork = &forks[i];
		// }
		// else
		// 	table->philos[i].second_fork = &forks[i - 1];
		i++;
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
		if (init_philo_mutexes(philo, table))
			return (ERROR);
		i++;
	}
	assign_forks(table, table->forks);
	return (SUCCESS);
}

int	init_table(t_table *table)
{
	int	retval;

	retval = 0;
	table->end_simulation = false;
	table->death = false;
	if (init_mutexes(table) != SUCCESS)
		return (ERROR);
	if (init_philos(table) != SUCCESS)
		return (ft_error(table, PHILO_INIT));
	return (SUCCESS);
}

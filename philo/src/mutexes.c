/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/17 19:35:53 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/19 13:11:11 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_mutexes(t_philo *philo, t_table *table)
{
	if (pthread_mutex_init(&philo->meals_m, NULL) != SUCCESS)
		return (ft_error(table, MUTEX_INIT));
	if (pthread_mutex_init(&philo->meal_time_m, NULL) != SUCCESS)
		return (ft_error(table, MUTEX_INIT));
	if (pthread_mutex_init(&philo->full_m, NULL) != SUCCESS)
		return (ft_error(table, MUTEX_INIT));
	return (SUCCESS);
}

int	init_forks(t_table *table)
{
	size_t	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->philo_count);
	if (!table->forks)
		return (ft_error(table, MALLOC));
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != SUCCESS)
			return (ft_error(table, MUTEX_INIT));
		i++;
	}
	return (SUCCESS);
}

int	init_prog_mutexes(t_table *table)
{
	size_t	i;

	table->prog_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ALL);
	if (!table->prog_m)
		return (ft_error(table, MALLOC));
	i = 0;
	while (i < ALL)
	{
		if (pthread_mutex_init(&table->prog_m[i], NULL) != SUCCESS)
			return (ft_error(table, MUTEX_INIT));
		i++;
	}
	return (SUCCESS);
}

int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->death_m, NULL) != SUCCESS)
		return (ft_error(table, MUTEX_INIT));
	if (init_forks(table) != SUCCESS)
		return (ERROR);
	if (init_prog_mutexes(table) != SUCCESS)
		return (ft_error(table, MUTEX_INIT));
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/17 19:35:53 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/17 19:36:38 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

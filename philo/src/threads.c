/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 17:13:33 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/19 15:38:21 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_table *table, size_t i)
{
	size_t	t;

	t = 0;
	while (t < i)
	{
		pthread_join(table->philo_threads[t], NULL);
		t++;
	}
}

int	create_threads(t_table *table)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&table->prog_m[START]);
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo_threads[i], NULL,
				&dinner_routine, &table->philos[i]) != SUCCESS)
		{
			pthread_mutex_unlock(&table->prog_m[START]);
			join_threads(table, i + 1);
			return (ft_error(table, PHILO));
		}
		i++;
	}
	table->start_simulation = gettime();
	pthread_mutex_unlock(&table->prog_m[START]);
	return (SUCCESS);
}

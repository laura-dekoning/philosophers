/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 17:13:33 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/23 17:33:53 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_table *table, size_t i)
{
	size_t	t;

	t = 0;
	while (t <= i)
	{
		pthread_join(table->philo_threads[i], NULL);
		t++;
	}
}

int	create_threads(t_table *table)
{
	size_t	i;

	i = 0;
	mutex_handle(&table->prog_m[START], LOCK);
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo_threads[i], NULL,
				&dinner_routine, &table->philos[i]) != SUCCESS)
		{
			mutex_handle(&table->prog_m[START], UNLOCK);
			join_threads(table, i);
			return (ft_error(table, PHILO));
		}
		i++;
	}
	mutex_handle(&table->prog_m[START], UNLOCK);
	return (SUCCESS);
}

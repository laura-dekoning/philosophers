/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:48:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/26 17:12:09 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	init_data(t_table *table)
{
	int	id;

	id = 0;
	table->end_simulation = false;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_count);
	while (id < table->philo_count)
	{
		table->forks[id].fork_id = id;
		id++;
	}
	return (SUCCESS);
}

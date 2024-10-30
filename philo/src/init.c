/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:48:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/30 17:43:54 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *data)
{
	(void)data;
	printf("Jeeej\n");
	return (NULL);
}

t_error	create_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i;
		if (pthread_create(table->p_ids[i], 0, philo_loop, &table->philos[i]) != SUCCESS)
			return (ERROR);
		
	}
}

t_error	alloc_table_data(t_table *table)
{
	int	id;

	id = 0;
	table->end_simulation = false;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_error(table, MALLOC));
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_count);
	if (!table->forks)
		return (ft_error(table, MALLOC));
	table->p_ids = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->p_ids)
		return (ft_error(table, MALLOC));
	while (id < table->philo_count)
	{
		table->forks[id].fork_id = id;
		id++;
	}
	return (SUCCESS);
}

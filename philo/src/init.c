/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:48:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/05 13:43:44 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *arg)
{
	int	philo_id;

	philo_id = *(int *)arg;
	PRINT_THINK(philo_id);
	PRINT_EAT(philo_id);
	PRINT_SLEEP(philo_id);
	PRINT_FORK(philo_id);
	PRINT_DIED(philo_id);
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
		if (pthread_create(table->pt_id[i], 0, philo_loop, &table->philos[i]) != SUCCESS)
			return (THREAD);
		i++;
	}
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->pt_id[i], NULL) != SUCCESS);
			return (THREAD);
		i++;
	}
}

t_error	init_table(t_table *table)
{
	int	id;
	int	x;

	x = 0;
	id = 0;
	table->end_simulation = false;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_error(table, MALLOC));
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_count);
	if (!table->forks)
		return (ft_error(table, MALLOC));
	table->pt_id = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->pt_id)
		return (ft_error(table, MALLOC));
	while (id < table->philo_count)
	{
		table->forks[id].fork_id = id;
		id++;
	}
	x = create_philos(table);
	if (x == THREAD)
		return (ft_error(table, THREAD_ERR));
	return (SUCCESS);
}

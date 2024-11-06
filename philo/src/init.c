/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:48:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/06 17:32:58 by lade-kon      ########   odam.nl         */
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

t_error	init_forks(t_table *table)
{
	int	i;

	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_count);
	if (!table->forks)
		return (MALLOC);
	i = 0;
	while (i < table->philo_count)
	{
		table->forks[i].fork_id = i;
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != SUCCESS)
			return (MUTEX_INIT);
		i++;
	}
	return (SUCCESS);
}

void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	nbr_philos;

	nbr_philos = philo->table->philo_count;
	philo->left_fork = &forks[(i + 1) % nbr_philos];
	philo->right_fork = &forks[i];
	if (i % 2 == 0)
	{
		philo->right_fork = &forks[i];
		philo->left_fork = &forks[(i + 1) % nbr_philos];
	}
}


t_error	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (MALLOC);
	table->pt_id = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->pt_id)
		return (MALLOC);
	i = 0;
	while (i < table->philo_count)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->meals_counter = 0;
		philo->last_meal_time = 0;
		philo->full = false;
		philo->table = table;
		assign_forks(philo, table->forks, i);
		if (pthread_create(table->pt_id[i], 0, philo_loop, &table->philos[i]) != SUCCESS)
			return (i);
		i++;

	t_fork	*left_fork;
	t_fork	*right_fork;

	}
	//if i == philo_count maak extra thread die monitor is die kijkt naar elke thread data
	//kijkt of is DEAD. monitor_loop heeft toegang nodig tot philo info (table) 
	if (i == table->philo_count)
		pthread_create(something, 0, monitor_loop, &arg);
	return (SUCCESS);
}
//figure out how you want to do the returns and error messages (where to free etc).
t_error	init_table(t_table *table)
{
	t_error	retval;

	retval = 0;
	table->end_simulation = false;
	retval = init_forks(table);
	retval = init_philos(table);
	if (retval != SUCCESS)
	{
		while (retval > 0)
		{
			if (pthread_join(table->pt_id[retval], NULL) != SUCCESS);
				return (THREAD_JOIN);
			retval--;
		}
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:48:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/07 13:51:43 by lade-kon      ########   odam.nl         */
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

int	init_forks(t_table *table)
{
	int	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->philo_count);
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

void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	int	nbr_philos;

	nbr_philos = philo->table->philo_count;
	philo->first_fork = &forks[(i + 1) % nbr_philos];
	philo->second_fork = &forks[i];
	if (i % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % nbr_philos];
	}
}


int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_error(table, MALLOC));
	table->pt_id = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->pt_id)
		return (ft_error(table, MALLOC));
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
	}

	return (SUCCESS);
}

//figure out how you want to do the returns and error messages (where to free etc).
int	init_table(t_table *table)
{
	int	retval;

	retval = 0;
	table->end_simulation = false;
	retval = inipthread_mutex_ts(table);
	retval = init_philos(table);
	if (retval != table->philo_count)
	{
		while (retval > 0)
		{
			if (pthread_join(table->pt_id[retval], NULL) != SUCCESS)
				return (ft_error(table, THREAD_JOIN));
			retval--;
		}
	}
	return (SUCCESS);
}

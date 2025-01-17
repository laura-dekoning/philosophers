/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 11:57:25 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/17 14:13:38 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (opcode == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		return (pthread_mutex_destroy(mutex));
	return (ERROR);
}

bool	all_philos_full(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		mutex_handle(&table->philos[i].philo_mutex, LOCK);
		if (table->philos[i].full == false)
		{
			mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
			return (false);
		}
		mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
		i++;
	}
	return (true);
}

bool	is_philo_dead(t_table *table, size_t time, size_t i)
{
	if (table->philos[i].last_meal_time == 0)
	{
		if ((time - table->start_simulation) > table->time_to_die)
		{
			write_status(DEAD, &table->philos[i]);
			return (true);
		}
	}
	else
	{
		if ((time - table->philos[i].last_meal_time) > table->time_to_die)
		{
			write_status(DEAD, &table->philos[i]);
			return (true);
		}
	}
	return (false);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	size_t	elapsed;
	size_t	time;
	int		id;

	elapsed = gettime();
	time = elapsed - philo->table->start_simulation;
	id = philo->philo_id;
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, FORK);
	else if (status == EATING && !simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, EAT);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, SLEEP);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, THINK);
	else if (status == DEAD && !simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, DIED);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

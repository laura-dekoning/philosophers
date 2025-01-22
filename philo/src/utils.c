/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 11:57:25 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/22 12:55:52 by lade-kon      ########   odam.nl         */
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
	t_philo	*philo;

	philo = &table->philos;
	i = 0;
	while (i < table->philo_count)
	{
		if (!get_bool(&philo[i].philo_mutex, &philo[i].full))
			return (false);
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

//Check if this is correct, maybe something else needs to happen if simulation is finished.
//But maybe just unlock and NOT print is fine. 
void	write_status(char *status, t_philo *philo)
{
	size_t	elapsed;
	size_t	time;
	int		id;

	elapsed = gettime();
	time = elapsed - philo->table->start_simulation;
	id = philo->philo_id;
	mutex_handle(&philo->table->prog_m[DISPLAY], LOCK);
	if (!simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, status);
	mutex_handle(&philo->table->prog_m[DISPLAY], UNLOCK);
}

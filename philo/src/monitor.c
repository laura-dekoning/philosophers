/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:01:39 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/23 16:07:29 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_philos_full(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	philo = table->philos;
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
			write_status(DIED, &table->philos[i]);
			return (true);
		}
	}
	else
	{
		if ((time - table->philos[i].last_meal_time) > table->time_to_die)
		{
			write_status(DIED, &table->philos[i]);
			return (true);
		}
	}
	return (false);
}

void	*monitor(t_table *table)
{
	size_t	time;
	size_t	i;

	while (1)
	{
		if (someone_died(table))
			return (NULL);
		if (everyone_full(table))
			return (NULL);
	}

	while (table->end_simulation == false)
	{
		i = 0;
		while (i < table->philo_count)
		{
			mutex_handle(&table->philos[i].philo_mutex, LOCK);
			time = gettime();
			if (is_philo_dead(table, time, i) == true)
			{
				set_bool(&table->table_mutex, &table->death, true);
				set_bool(&table->prog_m[STOP], &table->end_simulation, true);
				mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
				break ;
			}
			mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
			i++;
		}
		if (all_philos_full(table) == true)
			set_bool(&table->prog_m[STOP], &table->end_simulation, true);
	}
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:01:39 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/19 16:52:19 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	everyone_full(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	philo = table->philos;
	i = 0;
	while (i < table->philo_count)
	{
		if (!get_bool(&philo[i].full_m, &philo[i].full))
			return (false);
		i++;
	}
	set_bool(&table->prog_m[STOP], &table->end_simulation, true);
	return (true);
}

bool	philo_died(t_table *table, size_t i)
{
	size_t	time;

	time = gettime();
	if (table->philos[i].last_meal_time == 0)
	{
		if ((time - table->start_simulation) > table->time_to_die)
			return (true);
	}
	else
	{
		if ((time - table->philos[i].last_meal_time) > table->time_to_die)
			return (true);
	}
	return (false);
}

bool	someone_died(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[i].meal_time_m);
		if (philo_died(table, i) == true)
		{
			set_bool(&table->prog_m[STOP], &table->end_simulation, true);
			write_status(DIED, &table->philos[i]);
			pthread_mutex_unlock(&table->philos[i].meal_time_m);
			return (true);
		}
		pthread_mutex_unlock(&table->philos[i].meal_time_m);
		i++;
	}
	return (false);
}

void	monitor(t_table *table)
{
	while (1)
	{
		if (someone_died(table) == true)
			return ;
		if (table->eat_limit == true)
		{
			if (everyone_full(table) == true)
				return ;
		}
		usleep(200);
	}
	return ;
}

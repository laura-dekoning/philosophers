/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:01:39 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/23 16:23:01 by lade-kon      ########   odam.nl         */
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
		if (!get_bool(&philo[i].philo_mutex, &philo[i].full))
			return (false);
		i++;
	}
	return (true);
}

bool	philo_died(t_table *table, size_t i)
{
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
	size_t	time;
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		mutex_handle(&table->philos[i].philo_mutex, LOCK);
		time = gettime();
		if (philo_died(table, i) == true)
		{
			write_status(DIED, &table->philos[i]);
			set_bool(&table->table_mutex, &table->death, true);
			set_bool(&table->prog_m[STOP], &table->end_simulation, true);
			mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
			break ;
		}
		mutex_handle(&table->philos[i].philo_mutex, UNLOCK);
		i++;
	}

}

void	*monitor(t_table *table)
{

	while (1)
	{
		if (someone_died(table))
			return (NULL);
		if (everyone_full(table))
			return (NULL);
		usleep(500);
	}

	while (table->end_simulation == false)
	{
		if (all_philos_full(table) == true)
			set_bool(&table->prog_m[STOP], &table->end_simulation, true);
	}
	return (NULL);
}
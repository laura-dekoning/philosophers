/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/12 10:23:03 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/**
 * 1) All philos have to wait till ready, synchro start
 * 
 * 2) Endless philo loop
 */
void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);

	return (NULL);
}

int	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->meal_limit == 0)
		return (SUCCESS); //back to main, clean
	else if (table->philo_count == 1)
		;//TODO 
	else
	{
		while (i < table->philo_count)
		{
			if (pthread_create(table->pt_id[i], 0, dinner_routine, &table->philos[i]) != SUCCESS)
			{
				while (i >= 0)
				{
					pthread_join(table->pt_id[i], NULL);
					i--;
				}
				return (ft_error(table, "Threading"));
			}
			i++;
		}
	}
}

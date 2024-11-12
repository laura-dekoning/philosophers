/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/12 09:40:51 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_routine(void *arg)
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
			return (i);
		}
	}
}

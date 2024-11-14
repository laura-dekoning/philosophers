/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:15:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/14 14:02:12 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//BOOL
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	retval;

	pthread_mutex_lock(mutex);
	retval = *value;
	pthread_mutex_unlock(mutex);
	return (retval);
}

//LONG
void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	retval;

	pthread_mutex_lock(mutex);
	retval = *value;
	pthread_mutex_unlock(mutex);
	return (retval);
}

/**
 * To make clear if simulation is finished or not.
 */
bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 11:57:25 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/12/06 14:57:15 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Maybe look back in video at 41:00 for return handling
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

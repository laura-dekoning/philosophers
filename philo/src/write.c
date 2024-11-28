/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 13:44:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/27 13:41:51 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	size_t	elapsed;

	elapsed = gettime(MILLISECONDS);
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (debug)
		write_status_debug(status, philo, debug);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_finished(philo->table))
			PRINT_FORK(elapsed, philo->philo_id);
		else if (status == EATING && !simulation_finished(philo->table))
			PRINT_EAT(elapsed, philo->philo_id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			PRINT_SLEEP(elapsed, philo->philo_id);
		else if (status == THINKING && !simulation_finished(philo->table))
			PRINT_THINK(elapsed, philo->philo_id);
		else if (status == DEAD && !simulation_finished(philo->table))
			PRINT_DIED(elapsed, philo->philo_id);
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 13:44:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/12/06 15:13:50 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	size_t	elapsed;
	size_t	time;
	int		id;

	if (philo->full)
		return ;
	elapsed = gettime(MILLISECONDS);
	time = elapsed - philo->table->start_simulation;
	id = philo->philo_id;
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_finished(philo->table))
		printf(B_W"%-6ld"DEF"%d %s\n", time, id, FORK);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(B_G"%-6ld"DEF"%d %s\n", time, id, EAT);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(B_W"%-6ld"DEF"%d %s\n", time, id, SLEEP);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(B_W"%-6ld"DEF"%d %s\n", time, id, THINK);
	else if (status == DEAD && !simulation_finished(philo->table))
		printf(B_R"%-6ld"DEF"%d %s\n", time, id, DIED);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:30:08 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/12 19:51:23 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != SUCCESS)
		return (ft_error(NULL, "gettimeofday failed!"));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_usleep(size_t time_to, t_table *table)
{
	size_t	start;

	(void)table;
	start = gettime();
	while ((gettime() - start) < time_to)
	{
		if (simulation_finished(table))
			break ;
		usleep(500);
	}
}


// maakdeze skrrrtimedinges korter, want jou timer is geen smartwatch et snapdragon processor




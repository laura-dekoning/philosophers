/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:30:08 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/17 17:01:53 by lade-kon      ########   odam.nl         */
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

/**FIGURE OUT HOW THIS WORKS */
// line 38: to get a spinlock threshold
// line 43: SPINLOCK
// void	precise_usleep(size_t time_to, t_table *table)
// {
// 	size_t	start;
// 	size_t	elapsed;
// 	size_t	remain;

// 	start = gettime();
// 	while ((gettime() - start) < time_to)
// 	{
// 		if (simulation_finished(table))
// 			break ;
// 		elapsed = gettime() - start;
// 		remain = time_to - elapsed;
// 		if (remain > 1000)
// 			usleep(time_to / 2);
// 		else
// 		{
// 			while ((gettime() - start) < time_to)
// 				;
// 		}
// 	}
// }

void	precise_usleep(size_t time_to, t_table *table)
{
	size_t	start;

	(void)table;
	start = gettime();
	while ((gettime() - start) < time_to)
	{
		usleep(500);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:30:08 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/13 15:24:07 by lade-kon      ########   odam.nl         */
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

void	precise_usleep(size_t time_to)
{
	size_t	start;

	start = gettime();
	while ((gettime() - start) < time_to)
		usleep(100);
}

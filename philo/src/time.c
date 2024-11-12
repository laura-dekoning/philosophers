/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:30:08 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/12 09:39:20 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != SUCCESS)
		return (ft_error(NULL, "gettimeofday failed!"));
	if (time_code == SECONDS)
		return (time.tv_sec + (time.tv_usec * 1000000));
	else if (time_code == MILLISECONDS)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else if (time_code == MICROSECONDS)
		return ((time.tv_sec * 1000000) + time.tv_usec);
}

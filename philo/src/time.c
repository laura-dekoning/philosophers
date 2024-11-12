/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:30:08 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/12 10:19:59 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	gettimediff(struct timeval start, t_time_code time_code)
{
	size_t	current_time;
	size_t	start_time;

	current_time = gettime(time_code);
	if (time_code == SECONDS)
	{
		start_time = (start.tv_sec + (start.tv_usec * 1000000));
		return (current_time - start_time);
	}
	else if (time_code == MILLISECONDS)
	{
		start_time = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
		return (current_time - start_time);
	}
	else if (time_code == MICROSECONDS)
	{
		start_time = ((start.tv_sec * 1000000) + start.tv_usec);
		return (current_time - start_time);
	}
}

size_t	gettime(t_time_code time_code)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:50:56 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/11 17:06:12 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	
	data->philo_count = ft_atoi(argv[0]);
	data->time_die = ft_atoi(argv[1]);
	data->time_eat = ft_atoi(argv[2]);
	data->time_sleep = ft_atoi(argv[3]);
	if (argc == 6)
		data->eat_count = ft_atoi(argv[4]);
	return (data);
}

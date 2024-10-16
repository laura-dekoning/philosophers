/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:50:56 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/16 18:59:32 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_data(t_table *data)
{
	if (data->philo_count < 1 || data->philo_count > INT_MAX)
		return (ERROR);
	if (data->time_to_die < 1 || data->time_to_die > INT_MAX)
		return (ERROR);
	if (data->time_to_eat < 1 || data->time_to_eat > INT_MAX)
		return (ERROR);
	if (data->time_to_sleep < 1 || data->time_to_sleep > INT_MAX)
		return (ERROR);
	if (data->meal_limit < 1 || data->meal_limit > INT_MAX)
		return (ERROR);
	return (SUCCESS);
}

t_table	*init_data(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	
	table->philo_count = ft_atol(argv[0]);
	table->time_to_die = ft_atol(argv[1]);
	table->time_to_eat = ft_atol(argv[2]);
	table->time_to_sleep = ft_atol(argv[3]);
	if (argc == 6)
		table->meal_limit = ft_atol(argv[4]);
	if (check_data(table) == ERROR)
		return (error_exit(table, INT_ERROR));
	return (table);
}

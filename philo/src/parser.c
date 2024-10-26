/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:15:27 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/26 17:11:36 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	parse_input(t_table *table, int argc, char **argv)
{
	 if (ft_atol(argv[1], &table->philo_count) != SUCCESS)
	 	return (ERROR);
	 if (ft_atol(argv[2], &table->time_to_die) != SUCCESS)
	 	return (ERROR);
	 if (ft_atol(argv[3], &table->time_to_eat) != SUCCESS)
	 	return (ERROR);
	 if (ft_atol(argv[4], &table->time_to_sleep) != SUCCESS)
	 	return (ERROR);
	if (argc == 6)
	{
		if (ft_atol(argv[5], &table->meal_limit) != SUCCESS)
			return (ERROR);
	}
	else
		table->meal_limit = -1;
	print_table(table);
	return (SUCCESS);
}

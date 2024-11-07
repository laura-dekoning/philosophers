/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:15:27 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/07 13:43:48 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_table *table, int argc, char **argv)
{
	 if (ft_atoul(argv[1], &table->philo_count) != SUCCESS)
	 	return (ERROR);
	 if (ft_atoul(argv[2], &table->time_to_die) != SUCCESS)
	 	return (ERROR);
	 if (ft_atoul(argv[3], &table->time_to_eat) != SUCCESS)
	 	return (ERROR);
	 if (ft_atoul(argv[4], &table->time_to_sleep) != SUCCESS)
	 	return (ERROR);
	if (argc == 6)
	{
		table->eat_limit = true;
		if (ft_atoul(argv[5], &table->meal_limit) != SUCCESS)
			return (ERROR);
	}
	else
		table->meal_limit = -1;
	print_table(table);
	return (SUCCESS);
}

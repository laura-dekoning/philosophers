/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:15:26 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/12 11:06:40 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_data(t_table *data, int flag)
{
	if (data)
		free (data);
	return (flag);
}

int	ft_error(t_table *data, char *str)
{
	printf(B_R"Error\n"DEF);
	printf("%s\n", str);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (argc != 5 && argc != 6)
		return (ft_error(&table, ARGS));
	if (parse_input(&table, argc, argv) != SUCCESS)
		return (clean_data(&table, ERROR));
	if (init_table(&table) != SUCCESS)
		return (clean_data(&table, ERROR));
	if (dinner_start(&table) != SUCCESS)
		return (clean_data(&table, ERROR));
	return (clean_data(&table, SUCCESS));
}

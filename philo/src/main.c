/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:15:26 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/12 09:41:32 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_table *data, char *str)
{
	if (data)
		free(data);
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
		return (ERROR);
	if (init_table(&table) != SUCCESS)
		return (ERROR);
	if (dinner_start(&table) != SUCCESS)
		return (ERROR);
	// clean_table(&table);


	return (SUCCESS);
}

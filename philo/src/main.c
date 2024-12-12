/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:15:26 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/12/12 20:45:05 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_data(t_table *table, int flag)
{
	size_t	i;

	i = 0;
	mutex_handle(&table->table_mutex, DESTROY);
	mutex_handle(&table->write_mutex, DESTROY);
	while (i < table->philo_count)
	{
		mutex_handle(&table->forks[i], DESTROY);
		mutex_handle(&table->philos[i].philo_mutex, DESTROY);
		i++;
	}
	if (table->philos)
		free (table->philos);
	if (table->philo_threads)
		free (table->philo_threads);
	if (table->forks)
		free (table->forks);
	return (flag);
}

int	ft_error(t_table *data, char *str)
{
	printf(B_R"Error\n"DEF);
	printf("%s\n", str);
	if (data)
		clean_data(data, ERROR);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (argc != 5 && argc != 6)
		return (ft_error(&table, ARGS));
	// printf(B_P"Started "P"parsing\n"DEF);
	if (parse_input(&table, argc, argv) != SUCCESS)
		return (clean_data(&table, ERROR));
	// printf(B_G"Completed "G"parsing\n"DEF);
	// printf("--------------------------------------\n");
	// printf(B_O"Started "O"initialization\n"DEF);
	if (init_table(&table) != SUCCESS)
		return (clean_data(&table, ERROR));
	// print_table(&table);
	// print_philos(table.philos);
	// printf(B_G"Completed "G"initialization\n"DEF);
	// printf("--------------------------------------\n");
	// printf(B_Y"Started "Y"dinner\n"DEF);
	if (dinner_start(&table) != SUCCESS)
		return (clean_data(&table, ERROR));
	// printf(B_G"Completed "G"dinner\n"DEF);
	// print_philos(table.philos);
	// printf("--------------------------------------\n");
	return (clean_data(&table, SUCCESS));
}

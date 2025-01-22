/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:15:26 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/22 13:01:00 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_data(t_table *table, int flag)
{
	size_t	i;

	i = 0;
	mutex_handle(&table->table_mutex, DESTROY);
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
	if (table->monitor_thread)
		free (table->monitor_thread);
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
	if (parse_input(&table, argc, argv) != SUCCESS)
		return (ERROR);
	if (init_table(&table) != SUCCESS)
		return (clean_data(&table, ERROR));
	if (dinner_start(&table) != SUCCESS)
		return (clean_data(&table, ERROR));
	return (clean_data(&table, SUCCESS));
}

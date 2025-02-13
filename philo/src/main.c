/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:15:26 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/13 15:07:48 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_data(t_table *table, int flag)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&table->death_m);
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
		i++;
	}
	i = 0;
	while (i < ALL)
	{
		pthread_mutex_destroy(&table->prog_m[i]);
		i++;
	}
	if (table->philos)
		free (table->philos);
	if (table->philo_threads)
		free (table->philo_threads);
	if (table->forks)
		free (table->forks);
	if (table->prog_m)
		free(table->prog_m);
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
		return (ERROR);
	if (dinner_start(&table) != SUCCESS)
		return (ERROR);
	return (clean_data(&table, SUCCESS));
}

// 1 slot per koffer, anders data race, of what ever en.....EN ENNNNNNNNNN, 
// het gebruik van een locked variable, of het nou lezen of schrijven is, 
// probeer altijd te double checken of je het nou wel of niet moet MUTEXLOCKENNNN

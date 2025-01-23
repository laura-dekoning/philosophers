/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 15:23:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/23 15:16:31 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	size_t	i;
	printf(B_O"TABLE\n"DEF);
	printf("Philos: %li\n", table->philo_count);
	printf("Time to die: %li\n", table->time_to_die);
	printf("Time to eat: %li\n", table->time_to_eat);
	printf("Time to sleep: %li\n", table->time_to_sleep);
	printf("Meal limit: %li\n", table->meal_limit);
	printf("Start simulatoin: %li\n", table->start_simulation);
	printf("End simulation: %i\n", table->end_simulation);
	printf("All threads ready: %i\n", table->ready_to_start);
	// i = 0;
	// while (&table->philo_threads[i] != NULL)
	// 	i++;
	// printf("Amount of philo threads: %li\n", i);
	i = 0;
	while (i < table->philo_count)
	{
		printf("Pointer to philo_threads [%li]: %p\n", i, &table->philo_threads[i]);
		i++;
	}
	// while (&table->forks[i] != NULL)
	// 	i++;
	// printf("Amount of forks: %li\n", i);
	i = 0;
	while (i < table->philo_count)
	{
		printf("Pointer to fork mutex [%li]: %p\n", i, &table->forks[i]);
		i++;
	}
	i = 0;
	while (i < table->philo_count)
	{
		printf("Philo[%li] pointer to first fork: %p\n", i, &table->philos[i].first_fork);
		printf("Philo[%li] pointer to second fork: %p\n", i, &table->philos[i].second_fork);
		i++;
	}
}

void	print_philos(t_philo *philo)
{
	size_t	i;

	i = 0;
	printf(B_O"PHILOS\n"DEF);
	while (i < philo->table->philo_count)
	{
		printf("Index: %zu\n", i);
		printf("Philo id: %i\n", philo[i].philo_id);
		printf("Meals eaten: %li\n", philo[i].meals_eaten);
		printf("Last meal: %li\n", philo[i].last_meal_time);
		printf("Full: %i\n", philo[i].full);
		printf("--------------------------------------\n");
		i++;
	}
}

void	print_philo(t_philo *philo)
{
	printf("Philo id: %i\n", philo->philo_id);
	printf("Meals eaten: %li\n", philo->meals_eaten);
	printf("Last meal: %li\n", philo->last_meal_time);
	printf("Full: %i\n", philo->full);
}

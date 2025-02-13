/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 15:23:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/13 15:08:50 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	printf(B_O"TABLE\n"DEF);
	printf("Philos: %li\n", table->philo_count);
	printf("Time to die: %li\n", table->time_to_die);
	printf("Time to eat: %li\n", table->time_to_eat);
	printf("Time to sleep: %li\n", table->time_to_sleep);
	if (table->eat_limit == true)
		printf("Meal limit yes\n");
	else if (table->eat_limit == false)
		printf("Meal limit no\n");
	printf("Meal limit: %li\n", table->meal_limit);
	printf("Start simulatoin: %li\n", table->start_simulation);
	printf("End simulation: %i\n", table->end_simulation);
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
		if (philo->table->eat_limit == true)
			printf("Meal limit yes\n");
		else if (philo->table->eat_limit == false)
			printf("Meal limit no\n");
		printf("Meal limit: %li\n", philo->table->meal_limit);
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

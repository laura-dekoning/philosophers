/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 15:23:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/17 15:27:10 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	printf("Philos: %li\n", table->philo_count);
	printf("Time to die: %li\n", table->time_to_die);
	printf("Time to eat: %li\n", table->time_to_eat);
	printf("Time to sleep: %li\n", table->time_to_sleep);
	printf("Meal limit: %li\n", table->meal_limit);
}

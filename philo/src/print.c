/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 15:23:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/12/06 15:31:38 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	printf(B_P"TABLE\n"DEF);
	printf("Philos: %li\n", table->philo_count);
	printf("Time to die: %li\n", table->time_to_die);
	printf("Time to eat: %li\n", table->time_to_eat);
	printf("Time to sleep: %li\n", table->time_to_sleep);
	printf("Meal limit: %li\n", table->meal_limit);
}

void	print_philo(t_philo *philo)
{

}

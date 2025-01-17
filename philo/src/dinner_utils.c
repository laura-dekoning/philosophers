/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/16 19:30:59 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

/**
 * Eat routine
 * --------------------------------------------------------------
 * 1) grab forks
 * 2) eating : write eat, update last meal, update meals counter, 
 * 	  eventually bool full
 * 3) release forks
 */
void	eating(t_philo *philo)
{
	mutex_handle(philo->first_fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handle(philo->second_fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_size_t(&philo->philo_mutex, &philo->last_meal_time, gettime());
	philo->meals_eaten++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meal_limit > 0
		&& philo->meals_eaten == philo->table->meal_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(philo->first_fork, UNLOCK);
	mutex_handle(philo->second_fork, UNLOCK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/12 20:07:03 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_philo *philo)
{
	if (!simulation_finished(philo->table))
	{
		write_status(THINK, philo);
		precise_usleep((philo->table->time_to_eat), philo->table);
	}
}

void	thinking(t_philo *philo)
{
	if (!simulation_finished(philo->table))
	{
		write_status(THINK, philo);
	}
}

void	sleeping(t_philo *philo)
{
	if (!simulation_finished(philo->table))
	{
		write_status(SLEEP, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
	}
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
	if (!simulation_finished(philo->table))
	{
		mutex_handle(philo->first_fork, LOCK);
		write_status(FORK, philo);
		mutex_handle(philo->second_fork, LOCK);
		write_status(FORK, philo);
		set_size_t(&philo->philo_mutex, &philo->last_meal_time, gettime());
		if (philo->table->eat_limit == true)
			set_size_t(&philo->philo_mutex, &philo->meals_eaten, (philo->meals_eaten + 1));
		write_status(EAT, philo);
		precise_usleep(philo->table->time_to_eat, philo->table);
		if (philo->table->meal_limit > 0
			&& philo->meals_eaten == philo->table->meal_limit)
			set_bool(&philo->philo_mutex, &philo->full, true);
		mutex_handle(philo->first_fork, UNLOCK);
		mutex_handle(philo->second_fork, UNLOCK);
	}
}

// double check ff je mutex handle want die is een beetje returnie ish weird ofso idk

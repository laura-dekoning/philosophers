/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 09:05:35 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/19 17:11:26 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_philo *philo)
{
	write_status(THINK, philo);
	precise_usleep((philo->table->time_to_eat), philo->table);
}

void	thinking(t_philo *philo)
{
	write_status(THINK, philo);
}

void	sleeping(t_philo *philo)
{
	write_status(SLEEP, philo);
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
	if (!simulation_finished(philo->table))
	{
		pthread_mutex_lock(philo->first_fork);
		write_status(FORK, philo);
		pthread_mutex_lock(philo->second_fork);
		write_status(FORK, philo);
		set_size_t(&philo->meal_time_m, &philo->last_meal_time, gettime());
		if (philo->table->eat_limit == true)
			set_size_t(&philo->meals_m, &philo->meals_eaten, (philo->meals_eaten + 1));
		write_status(EAT, philo);
		precise_usleep(philo->table->time_to_eat, philo->table);
		pthread_mutex_unlock(philo->second_fork);
		pthread_mutex_unlock(philo->first_fork);
		if (philo->table->meal_limit > 0
			&& philo->meals_eaten == philo->table->meal_limit)
			set_bool(&philo->full_m, &philo->full, true);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:22:56 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/05 17:37:04 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <inttypes.h>


typedef struct s_fork
{
	pthread_mutex_t	fork; //a fork is a mutex
	int				fork_id;
}					t_fork;

typedef	struct s_table	t_table;

/**
 * @brief PHILO
 * 
 * @param philo_id: Each philo has a number ranging from 1 to philo_count.
 * @param meals_counter: Counts the amount of meals the philo had so far.
 * ./philo 5 800 200 200 [5]
 */
typedef struct s_philo
{
	int		philo_id;
	int		meals_counter;
	size_t	last_meal_time; //time passed from last meal
	bool	full;
	t_fork	*left_fork;
	t_fork	*right_fork;
	t_table	*table;
}			t_philo;

/**
 * @brief TABLE
 * 
 * @param philo_count: Number of philos and also number of forks on table.
 * @param time_to_die (in milliseconds): If a philo didn’t start eating 
 * time_to_die milliseconds since the beginning of their last meal or the 
 * beginning of the simulation, they die.
 * @param time_to_eat (in milliseconds): The time it takes for a philo to eat.
 * During that time, they will need to hold two forks.
 * @param time_to_sleep (in milliseconds): The time a philo will be sleeping.
 * @param meal_limit (optional argument): If all philos have eaten at least 
 * meal_limit times, the simulation stops. If not specified, the simulation 
 * stops when a philo dies.
 * 
 * ./philo 5 800 200 200 [5]
 */
typedef	struct s_table
{
	size_t		philo_count;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		meal_limit; // [5] || FLAG if -1
	size_t		start_simulation; //when simulation is started
	size_t		end_simulation; //a philo dies or when all philos are full
	bool		death;
	t_fork		*forks; //array of forks
	t_philo		*philos; //array of philos
	pthread_t	*pt_id; // a philo is a thread, this is the philothread_id
}				t_table;

// struct timeval {
//     time_t      tv_sec;     // seconds
//     suseconds_t tv_usec;    // microseconds
// };

#endif
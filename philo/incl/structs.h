/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:22:56 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/17 17:08:02 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <inttypes.h>

/**
 * @brief makes code more readable with smaller variable name.
 */
typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	t_mutex	fork; //a fork is a mutex
	int		fork_id;
}			t_fork;

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
	long	last_meal_time; //time passed from last meal
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
	long		philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meal_limit; // [5] || FLAG if -1
	long		start_simulation; //when simulation is started
	long		end_simulation; //a philo dies or when all philos are full
	t_fork		*forks; //array of forks
	t_philo		*philos; //array of philos
	pthread_t	thread_id; // a philo is a thread
}				t_table;

// struct timeval {
//     time_t      tv_sec;     // seconds
//     suseconds_t tv_usec;    // microseconds
// };

#endif
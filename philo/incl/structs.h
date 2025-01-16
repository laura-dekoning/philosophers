/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:22:56 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/16 15:05:44 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <inttypes.h>
# include <sys/time.h>

typedef struct s_table	t_table;


/**
 * @brief PHILO
 * 
 * @param philo_id: Each philo has a number ranging from 1 to philo_count.
 * @param meals_counter: Counts the amount of meals the philo had so far.
 * ./philo 5 800 200 200 [5]
 */
typedef struct s_philo
{
	int				philo_id;
	size_t			meals_eaten;
	size_t			last_meal_time; //time passed from last meal
	bool			full;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	philo_mutex; //useful for races with the monitor
	t_table			*table;
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
typedef struct s_table
{
	size_t			philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meal_limit; // [5] || FLAG if -1
	size_t			start_simulation; //time when simulation is started
	struct timeval	start_time;
	bool			end_simulation; //a philo dies or when all philos are full
	bool			all_threads_ready;
	bool			eat_limit;
	t_philo			*philos; //array of philos
	pthread_t		*philo_threads; // a philo is a thread, this is the id
	pthread_mutex_t	*forks; //array of forks
	pthread_mutex_t	table_mutex; //avoid races while reading from table
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	time_mutex; //useful for races with the monitor
}					t_table;

// struct timeval {
//     time_t      tv_sec;     // seconds
//     suseconds_t tv_usec;    // microseconds
// };
typedef enum s_time_code
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}	t_time_code;

typedef enum s_opcode
{
	LOCK,
	UNLOCK,
	CREATE,
	INIT,
	JOIN,
	DESTROY
}	t_opcode;

typedef enum s_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD
}	t_philo_status;

#endif
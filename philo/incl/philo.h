/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:16:05 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/23 19:37:19 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "colors.h"
# include "macros.h"
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h> 
# include <limits.h>
# include <stdbool.h>
# include <inttypes.h>

/*Philosopher number 1 sits next to philosopher number 
number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and 
philosopher number N + 1*/

/*About the logs of your program:
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
• A displayed state message should not be mixed up with another message.
• A message announcing a philosopher died should be displayed no more than
 10 ms after the actual death of the philosopher.
• Again, philosophers should avoid dying!*/

/*The specific rules for the mandatory part are:
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. Therefore, if 
there are several philosophers, each philosopher has a fork on their left 
side and a fork on their right side. If there is only one philosopher, 
there should be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect 
the forks state with a mutex for each of them.*/

int		ft_error(t_table *data, char *str);
int		parse_input(t_table *table, int argc, char **argv);
int		ft_atoul(const char *str, size_t *num);
int		init_table(t_table *table);
void	print_table(t_table *table);
void	print_philos(t_philo *philo);
void	print_philo(t_philo *philo);
int		clean_data(t_table *table, int flag);

//DINNER
int		dinner_start(t_table *table);
void	*dinner_routine(void *data);

//DINNER UTILS
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	waiting(t_philo *philo);

//UTILS
void	write_status(char *status, t_philo *philo);

//MONITOR
void	monitor(t_table *table);
bool	everyone_full(t_table *table);
bool	someone_died(t_table *table);
bool	philo_died(t_table *table, size_t i);


// GETTERS & SETTERS
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_size_t(pthread_mutex_t *mutex, size_t *dest, size_t value);
size_t	get_size_t(pthread_mutex_t *mutex, size_t *value);
bool	simulation_finished(t_table *table);

// TIME UTILS
size_t	gettime(void);
void	precise_usleep(size_t usec, t_table *table);

//THREADS
int	create_threads(t_table *table);
void	join_threads(t_table *table, size_t i);

// MUTEXES
int		mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
int		init_forks(t_table *table);
int		init_prog_mutexes(t_table *table);
int		init_mutexes(t_table *table);

#endif
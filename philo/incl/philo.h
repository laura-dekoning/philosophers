/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:16:05 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/17 18:43:15 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "colors.h"
# include "errors.h"
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h> //usleep - suspend execution for microsecond intervals
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
• A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
• Again, philosophers should avoid dying!*/

/*The specific rules for the mandatory part are:
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.*/

# define ERROR -1
# define SUCCESS 0

# define ARGS_ERROR -1
# define INT_ERROR -2



void	ft_error(t_table *table, char *str);
void	parse_input(t_table *table, int argc, char **argv);
long	ft_atol(const char *str);
t_table	*init_data(int argc, char **argv);
void	print_table(t_table *table);


#endif
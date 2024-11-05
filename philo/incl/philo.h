/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:16:05 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/05 13:43:10 by lade-kon      ########   odam.nl         */
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
# include <string.h>
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

// Messages for philos
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

#ifdef PRETTY_MODE
	// Define colors from red to green
	# define DEF   "\033[0;39m"  // Default color
	# define RED   "\033[0;91m"  // Light Red
	# define ORANGE "\033[0;93m" // Light Yellow/Orange
	# define YELLOW "\033[1;93m" // Bright Yellow
	# define LGREEN "\033[0;92m" // Light Green
	# define GREEN  "\033[1;92m" // Bright Green

    // Macros to print each action with a specific color
    # define PRINT_FORK(id) printf(ORANGE "%d %s" DEF "\n", id, FORK)
    # define PRINT_EAT(id)  printf(GREEN "%d %s" DEF "\n", id, EAT)
    # define PRINT_SLEEP(id) printf(YELLOW "%d %s" DEF "\n", id, SLEEP)
    # define PRINT_THINK(id) printf(LGREEN "%d %s" DEF "\n", id, THINK)
    # define PRINT_DIED(id) printf(RED "%d %s" DEF "\n", id, DIED)
#else
    // Default printing without color if PRETTY_MODE is not defined
    # define PRINT_FORK(id) printf("%d %s\n", id, FORK)
    # define PRINT_EAT(id)  printf("%d %s\n", id, EAT)
    # define PRINT_SLEEP(id) printf("%d %s\n", id, SLEEP)
    # define PRINT_THINK(id) printf("%d %s\n", id, THINK)
    # define PRINT_DIED(id) printf("%d %s\n", id, DIED)
#endif

int		ft_error(t_table *data, int flag);
t_error	parse_input(t_table *table, int argc, char **argv);
t_error	ft_atol(const char *str, size_t *num);
t_error	init_table(t_table *table);
void	print_table(t_table *table);


#endif
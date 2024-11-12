/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   macros.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 18:40:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/12 09:25:42 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifndef MACROS_H
# define MACROS_H

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define ERROR 1

# define NO_NEG "Numbers can't be negative bro"
# define TOO_BIG "Numbers can't be this big bro"
# define NO_NUM "You have to give me numbers bro!"
# define ARGS "This is not the right amount of arguments!"
# define MALLOC "Something went wrong with malloc =("
# define THREAD_CREATE "Oh no, something went wrong while creating threads."
# define MUTEX_INIT "Mutex initialization went wrong."
# define THREAD_JOIN "Joining threads didn't work appropriately."

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

#endif
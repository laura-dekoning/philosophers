/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   macros.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 18:40:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/16 19:21:32 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include "philo.h"

# define SUCCESS 0
# define ERROR 1

// Error messages
# define NO_NEG "Numbers can't be negative bro"
# define TOO_BIG "Numbers can't be this big bro"
# define NO_NUM "You have to give me numbers bro!"
# define ARGS "This is not the right amount of arguments!"
# define MALLOC "Something went wrong with malloc =("
# define THREAD_CREATE "Oh no, something went wrong while creating threads."
# define MUTEX_INIT "Mutex initialization went wrong."
# define THREAD_JOIN "Joining threads didn't work appropriately."
# define PHILO "Something went wrong will creating philo threads."
# define MONITOR "Something went wrong will creating the monitoring thread."

// Messages for philos
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

#endif
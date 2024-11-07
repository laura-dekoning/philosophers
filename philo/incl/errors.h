/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 18:40:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/07 13:43:04 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifndef ERRORS_H
# define ERRORS_H

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

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 18:40:47 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/26 16:09:55 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifndef ERRORS_H
# define ERRORS_H

# define NEGATIVE_ERR "Numbers can't be negative bro"
# define TOO_BIG_ERR "Numbers can't be this big bro"
# define NO_NUM_ERR "You have to give me numbers bro!"
# define ARGS_ERR "This is not the right amount of arguments!"

typedef enum e_error 
{
	SUCCESS = 0,
	ERROR = -1,
	NO_NEG = -2,
	TOO_BIG = -3,
	NO_NUM = -4,
	ARGS = -5
} 	t_error;

#endif
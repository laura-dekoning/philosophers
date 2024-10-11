/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:16:05 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/11 17:08:23 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "colors.h"
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <inttypes.h>

# define ERROR -1
# define SUCCESS 0


# define ARGS 1


void	error_msg(int flag);
int		ft_atoi(const char *str);
t_data	*init_data(int argc, char **argv);


#endif
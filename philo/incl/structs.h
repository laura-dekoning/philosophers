/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:22:56 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/11 16:41:14 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <inttypes.h>

typedef	struct s_data
{
	int	philo_count;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	eat_count;

}	t_data;


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   synchro_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 14:04:50 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/14 14:06:37 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * SPINLOCK to synchronize philos start
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}
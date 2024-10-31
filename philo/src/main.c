/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:15:26 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/31 18:42:49 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (argc != 5 && argc != 6)
		return (ft_error(&table, ARGS));
	if (parse_input(&table, argc, argv) != SUCCESS)
		return (ft_error(&table, ERROR));
	if (init_table(&table) != SUCCESS)
		return (ft_error(&table, ERROR));
	// dinner_start(&table);
	// clean_table(&table);


	return (SUCCESS);



// 	pthread_t	thread1;
// 	pthread_mutex_t	mutex;
// 	pthread_mutex_lock_t	mutex_lock;

// 	pthread_create(&thread1, NULL, &function, NULL);
// 	pthread_join(&thread1, NULL);
// 	pthread_mutex_init(&mutex_lock, NULL);
// 	pthread_mutex_lock(&mutex_lock);
// //my code here
// 	pthread_mutex_unlock(&mutex_lock);
}

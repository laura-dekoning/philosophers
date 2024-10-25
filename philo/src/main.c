/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:15:26 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/25 13:57:28 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		error_exit(NULL, "This is not the right amount of arguments!");
	if (parse_input(table, argc, argv) < 0)
		return (-1);
	// data_init(&table);
	// dinner_start(&table);
	// clean_table(&table);


	return (0);



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

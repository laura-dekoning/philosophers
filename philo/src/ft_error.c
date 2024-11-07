/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:42:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/07 13:51:43 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_table *data, char *str)
{
	printf(B_R"Error\n"DEF);
	printf("%s\n", str);
	if (data)
		free(data);
	return (ERROR);
}

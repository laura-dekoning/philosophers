/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:42:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/06 17:30:40 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_table *data, int flag)
{
	char	*str;

	str = NULL;
	if (flag == TOO_BIG)
		str = TOO_BIG_ERR;
	else if (flag == NO_NEG)
		str = NEGATIVE_ERR;
	else if (flag == NO_NUM)
		str = NO_NUM_ERR;
	else if (flag == ARGS)
		str = ARGS_ERR;
	else if (flag == MALLOC)
		str = MALLOC_ERR;
	else if (flag == ERROR)
	{
		if (data)
			free(data);
		return (ERROR);		
	}
	printf(B_R"Error\n"DEF);
	printf("%s\n", str);
	if (data)
		free(data);
	return (ERROR);
}

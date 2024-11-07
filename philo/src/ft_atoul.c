/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoul.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 15:01:22 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/11/07 13:51:43 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static int	ft_numlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i++;
	return (i);
}

static int valid_input(const char *str, const char **num_start)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (ft_error(NULL, NO_NEG));
	if (ft_isdigit(*str) == false)
		return (ft_error(NULL, NO_NUM));
	if (ft_numlen(str) > 10)
		return (ft_error(NULL, TOO_BIG));
	*num_start = str;
	return (SUCCESS);
}


int	ft_atoul(const char *str, size_t *num)
{
	size_t		number;
	const char	*num_start;

	num_start = NULL;
	number = 0;

	if (valid_input(str, &num_start) != SUCCESS)
		return (ERROR); 
	str = num_start;
	while (ft_isdigit(*str) == true)
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (number > INT_MAX)
		return (ft_error(NULL, TOO_BIG));
	*num = number;
	return (SUCCESS);
}


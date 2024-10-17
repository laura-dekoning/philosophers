/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 15:01:22 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/17 15:23:16 by lade-kon      ########   odam.nl         */
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

static const char	*valid_input(const char *str)
{
	const char	*number;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit(NULL, "Numbers can't be negative bro");
	if (ft_isdigit(*str) == false)
		error_exit(NULL, "You have to give me numbers bro!");
	number = str;
	if (ft_numlen(str) > 10)
		error_exit(NULL, "Numbers can't be this big bro");
	return (number);
}


long	ft_atol(const char *str)
{
	long	number;

	number = 0;
	str = valid_input(str);
	while (ft_isdigit(*str) == true)
	{
		number = number * 10 + (*str - '0');
		++str;
	}
	if (number > INT_MAX)
		error_exit(NULL, "Numbers can't be this big bro");
	return (number);
}

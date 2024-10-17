/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 15:01:22 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/17 18:50:35 by lade-kon      ########   odam.nl         */
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
		return (NO_NEG);
	if (ft_isdigit(*str) == false)
		return (NO_NUM);
	number = str;
	if (ft_numlen(str) > 10)
		return (TOO_BIG);
	return (number);
}

static long	error_check(const char *str)
{
	if (str == NO_NEG)
		return (NEGATIVE);
	else if (str == TOO_BIG)
		return (ABOVE_INT_MAX);
	else if (str == NO_NUM)
		return (NOT_NUM);
	return (SUCCESS);
}

long	ft_atol(const char *str)
{
	long	number;
	int		return_val;

	return_val = 0;
	number = 0;
	str = valid_input(str);
	return_val = error_check(str);
	if (return_val != 0)
		return (return_val);
	while (ft_isdigit(*str) == true)
	{
		number = number * 10 + (*str - '0');
		++str;
	}
	if (number > INT_MAX)
		return (ABOVE_INT_MAX);
	return (number);
}

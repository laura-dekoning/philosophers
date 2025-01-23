/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:15:27 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/01/23 19:33:58 by lade-kon      ########   odam.nl         */
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

static int	valid_input(const char *str, const char **num_start)
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

int	parse_input(t_table *table, int argc, char **argv)
{
	if (ft_atoul(argv[1], &table->philo_count) != SUCCESS)
		return (ERROR);
	if (ft_atoul(argv[2], &table->time_to_die) != SUCCESS)
		return (ERROR);
	if (ft_atoul(argv[3], &table->time_to_eat) != SUCCESS)
		return (ERROR);
	if (ft_atoul(argv[4], &table->time_to_sleep) != SUCCESS)
		return (ERROR);
	if (argc == 6)
	{
		table->eat_limit = true;
		if (ft_atoul(argv[5], &table->meal_limit) != SUCCESS)
			return (ERROR);
	}
	else
		table->meal_limit = -1;
	return (SUCCESS);
}

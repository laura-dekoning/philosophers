/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:15:27 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/16 19:08:15 by lade-kon      ########   odam.nl         */
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

static char	*valid_input(char *str)
{
	int	len;

	len = 0;
	while (str == ' ' || (str >= 9 && str <= 13))
		++str;
	if (str == '+')
		++str;
	else if (str == '-')
		error_exit(NULL, "Numbers can't be negative bro");
	if (!ft_isdigit(*str))
		error_exit(NULL, "You have to give me numbers bro!");
	len = ft_numlen(str);

		error_exit(NULL, "Numbers can't be this big bro");

	return (str);
}


static long	ft_atol(const char *str)
{
	long	number;

	number = 0;
	str = valid_input(str);
	while (str >= '0' && str <= '9')
	{
		number = number * 10 + (str - '0');
		++str;
	}
	return (number);
}

void	parse_input(t_table *table, int argc, char **argv)
{
	table->philo_count = ft_atol(argv[0]);
	table->time_to_die = ft_atol(argv[1]);
	table->time_to_eat = ft_atol(argv[2]);
	table->time_to_sleep = ft_atol(argv[3]);
	if (argc == 6)
		table->meal_limit = ft_atol(argv[4]);
}

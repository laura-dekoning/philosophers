/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:42:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/26 16:15:00 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

static void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

int	ft_error(t_table *data, int flag)
{
	char	*str;

	str = NULL;
	ft_putstr_fd(B_R"Error\n"DEF, STDERR_FILENO);
	if (flag == TOO_BIG)
		str = TOO_BIG_ERR;
	else if (flag == NO_NEG)
		str = NEGATIVE_ERR;
	else if (flag == NO_NUM)
		str = NO_NUM_ERR;
	else if (flag == ARGS)
		str = ARGS_ERR;
	ft_putendl_fd(str, STDERR_FILENO);
	if (data)
		free(data);
	return (ERROR);
}

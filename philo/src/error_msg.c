/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:42:44 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/10/11 16:47:15 by lade-kon      ########   odam.nl         */
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

static void	ft_puterror_fd(char *str, int fd)
{
	ft_putstr_fd(B_R"Error\n"DEF, fd);
	ft_putendl_fd(str, fd);
	exit(EXIT_FAILURE);
}

void	error_msg(int flag)
{
	if (flag == ARGS)
		ft_puterror_fd("Not the right amount of arguments!", STDERR_FILENO);
}

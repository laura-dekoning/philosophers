/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 11:57:25 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/13 12:25:14 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (1);
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
 
void	write_status(char *status, t_philo *philo)
{
	size_t	elapsed;
	size_t	time;
	int		id;

	pthread_mutex_lock(&philo->table->prog_m[DISPLAY]);
	elapsed = gettime();
	time = elapsed - philo->table->start_simulation;
	id = philo->philo_id;
	if (get_bool(&philo->table->table_mutex, &philo->table->death) == true)
	{
		if (ft_strcmp("died", status))
			printf("%-6ld%d %s\n", time, id, status);
		pthread_mutex_unlock(&philo->table->prog_m[DISPLAY]);
		return ;
	}
	else if (!simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, status);
	pthread_mutex_unlock(&philo->table->prog_m[DISPLAY]);
}

// lock unlock alleen dat ene wat je wilt locken en niet perongeluk meerdere objecten of variabelen locken anders computer traag brrr

// check write_status function

// 
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 11:57:25 by lade-kon      #+#    #+#                 */
/*   Updated: 2025/02/13 11:37:46 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (opcode == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		return (pthread_mutex_destroy(mutex));
	return (ERROR);
}

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

//Check if this is correct, maybe something else needs to happen if simulation is finished.
//But maybe just unlock and NOT print is fine. 
void	write_status(char *status, t_philo *philo)
{
	size_t	elapsed;
	size_t	time;
	int		id;

	mutex_handle(&philo->table->prog_m[DISPLAY], LOCK);
	elapsed = gettime();
	time = elapsed - philo->table->start_simulation;
	id = philo->philo_id;
	if (get_bool(&philo->table->table_mutex, &philo->table->death) == true)
	{
		if (ft_strcmp("died", status))
			printf("%-6ld%d %s\n", time, id, status);
		mutex_handle(&philo->table->prog_m[DISPLAY], UNLOCK);
		return ;
	}
	else if (!simulation_finished(philo->table))
		printf("%-6ld%d %s\n", time, id, status);
	mutex_handle(&philo->table->prog_m[DISPLAY], UNLOCK);
}

// lock unlock alleen dat ene wat je wilt locken en niet perongeluk meerdere objecten of variabelen locken anders computer traag brrr

// check write_status function

// 
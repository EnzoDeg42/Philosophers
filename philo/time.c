/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:08:06 by edegraev          #+#    #+#             */
/*   Updated: 2024/07/04 10:08:16 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error: gettimeofday\n", 20);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	if (milliseconds <= 0)
		return ;
	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(milliseconds / 10);
}

void	await(t_philo *philo, int nb_philo, int time_to_eat)
{
	if (nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 1)
		{
			printf_mutex(philo->sys, philo, "is thinking\n");
			ft_usleep(time_to_eat * 1000);
		}
	}
	else if (philo->id % 2 == 1)
	{
		if (philo->id == nb_philo)
		{
			printf_mutex(philo->sys, philo, "is thinking\n");
			ft_usleep(time_to_eat * 1000 * 2);
		}
		else if (philo->id % 2 == 1)
		{
			printf_mutex(philo->sys, philo, "is thinking\n");
			ft_usleep(time_to_eat * 1000);
		}
	}
}

void	routine_start_delay(t_philo *philo)
{
	while (get_time() < philo->start_time)
		continue ;
	if (philo->id % 2 != 0)
	{
		printf_mutex(philo->sys, philo, "is thinking\n");
		ft_usleep(philo->eat_time);
	}
	else if (philo->id + 1 == philo->n_philo && philo->id % 2 == 0)
		printf_mutex(philo->sys, philo, "is thinking\n");
}

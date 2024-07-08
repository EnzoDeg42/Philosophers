/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:15:25 by edegraev          #+#    #+#             */
/*   Updated: 2024/07/04 10:07:07 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philos_eat_enough(t_sys *sys, t_philo *philo)
{
	int		i;

	if (sys->n_eat == -1)
		return (false);
	i = 0;
	while (i < sys->n_philo)
	{
		pthread_mutex_lock(&sys->sync_mutex);
		if (sys->philo[i].eat_count < sys->n_eat)
		{
			pthread_mutex_unlock(&sys->sync_mutex);
			return (false);
		}
		pthread_mutex_unlock(&sys->sync_mutex);
		i++;
	}
	return (true);
}

static bool	philos_died(t_sys *sys, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sys->n_philo)
	{
		pthread_mutex_lock(&sys->sync_mutex);
		if (sys->philo[i].last_meal != 1
			&& get_time() - sys->philo[i].last_meal > (size_t)sys->time_to_die)
		{
			pthread_mutex_unlock(&sys->sync_mutex);
			printf_mutex(sys, &sys->philo[i], "died\n");
			set_end(sys);
			return (true);
		}
		pthread_mutex_unlock(&sys->sync_mutex);
		i++;
	}
	return (false);
}

void	*monitor_routine(t_sys *sys)
{
	while (get_time() < sys->start_time)
		usleep(1);
	while (true)
	{	
		if (philos_eat_enough(sys, sys->philo))
			return (set_end(sys), NULL);
		if (philos_died(sys, sys->philo))
			return (NULL);
		usleep(1);
	}
	return (NULL);
}

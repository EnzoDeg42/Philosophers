/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:17:03 by edegraev          #+#    #+#             */
/*   Updated: 2024/07/04 09:18:20 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(t_sys *sys, t_philo *philo, char *str)
{
	pthread_mutex_lock(&sys->sync_mutex);
	if (sys->end)
	{
		pthread_mutex_unlock(&sys->sync_mutex);
		return ;
	}
	pthread_mutex_unlock(&sys->sync_mutex);
	pthread_mutex_lock(&sys->printf_mutex);
	printf("%ld %d %s", get_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(&sys->printf_mutex);
}

bool	set_end(t_sys *sys)
{
	pthread_mutex_lock(&sys->sync_mutex);
	sys->end = true;
	pthread_mutex_unlock(&sys->sync_mutex);
	return (true);
}

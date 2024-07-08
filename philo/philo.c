/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:29:22 by edegraev          #+#    #+#             */
/*   Updated: 2024/07/04 10:10:09 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left;
		second_fork = philo->right;
	}
	else
	{
		first_fork = philo->right;
		second_fork = philo->left;
	}
	pthread_mutex_lock(first_fork);
	printf_mutex(philo->sys, philo, "has taken a fork\n");
	pthread_mutex_lock(second_fork);
	printf_mutex(philo->sys, philo, "has taken a fork\n");
}

static void	untake_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
	else
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	printf_mutex(philo->sys, philo, "is eating\n");
	pthread_mutex_lock(&philo->sys->sync_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->sys->sync_mutex);
	pthread_mutex_lock(&philo->sys->sync_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->sys->sync_mutex);
	ft_usleep(philo->eat_time);
	untake_forks(philo);
}

static bool	routine_end_delay(t_philo *philo)
{
	if (philo->n_philo % 2 == 1)
	{
		if (((philo->eat_time * 2) - philo->sleep_time) > 0)
		{
			ft_usleep((philo->eat_time * 2) - philo->sleep_time);
			if (is_end(philo))
				return (true);
		}
	}
	else if (philo->n_philo % 2 == 0)
	{
		if ((philo->eat_time - philo->sleep_time) > 0)
		{
			ft_usleep(philo->eat_time - philo->sleep_time);
			if (is_end(philo))
				return (true);
		}
	}
	else if (is_end(philo))
		return (true);
	return (false);
}

void	*routine(t_philo *philo)
{
	routine_start_delay(philo);
	if (is_end(philo))
		return (NULL);
	while (true)
	{
		eat(philo);
		if (is_end(philo))
			return (NULL);
		printf_mutex(philo->sys, philo, "is sleeping\n");
		ft_usleep(philo->sleep_time);
		if (is_end(philo))
			return (NULL);
		printf_mutex(philo->sys, philo, "is thinking\n");
		if (routine_end_delay(philo))
			return (NULL);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:24:51 by edegraev          #+#    #+#             */
/*   Updated: 2024/07/04 10:25:05 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->sys->sync_mutex);
	if (philo->sys->end)
	{
		pthread_mutex_unlock(&philo->sys->sync_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->sys->sync_mutex);
	return (false);
}

void	*start_only_one(t_philo *philo)
{
	printf("0 1 is thinking\n");
	printf("0 1 has taken a fork\n");
	printf("%d 1 died\n", philo->sys->time_to_die);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_sys	sys;
	int		i;

	if (!sys_init(&sys, ac, av) || !philo_init(&sys))
		return (1);
	if (sys.n_philo == 1)
	{
		pthread_create(&sys.philo[0].thread, NULL,
			(void *(*)(void *))start_only_one, &sys.philo[0]);
		pthread_join(sys.philo[0].thread, NULL);
		return (0);
	}
	i = -1;
	while (++i < sys.n_philo)
		pthread_create(&sys.philo[i].thread, NULL,
			(void *(*)(void *))routine, &sys.philo[i]);
	pthread_create(&sys.monitor, NULL,
		(void *(*)(void *))monitor_routine, &sys);
	i = 0;
	while (i < sys.n_philo)
		pthread_join(sys.philo[i++].thread, NULL);
	pthread_join(sys.monitor, NULL);
	return (0);
}

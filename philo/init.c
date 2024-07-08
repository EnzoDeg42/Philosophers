/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:56:28 by edegraev          #+#    #+#             */
/*   Updated: 2024/07/04 10:13:56 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define E_N_PHILO "Error: number_of_philosophers must be between 1 and 200\n"
#define E_T_DIE "Error: time_to_die must be between 60 and INT_MAX\n"
#define E_T_EAT "Error: time_to_eat must be between 60 and INT_MAX\n"
#define E_T_SLEEP "Error: time_to_sleep must be between 60 and INT_MAX\n"
#define E_N_EAT_1 "Error: number_of_times_each_philosopher_must_eat must "
#define E_N_EAT_2 "be between 1 and INT_MAX\n" 
#define U_1 "usage: philo number_of_philosophers time_to_die time_to_eat "
#define U_2 "time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

static bool	sys_init_check(t_sys *sys, int ac, char **av)
{
	long long	result;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(U_1, 2);
		return (ft_putstr_fd(U_2, 2), false);
	}
	result = ft_atoll(av[1]);
	if (result < 1 || result > 200)
		return (ft_putstr_fd(E_N_PHILO, 2), false);
	sys->n_philo = (int)result;
	result = ft_atoll(av[2]);
	if (result < 60 || result > INT_MAX)
		return (ft_putstr_fd(E_T_DIE, 2), false);
	sys->time_to_die = (int)result;
	result = ft_atoll(av[3]);
	if (result < 60 || result > INT_MAX)
		return (ft_putstr_fd(E_T_EAT, 2), false);
	sys->eat_time = (int)result;
	result = ft_atoll(av[4]);
	if (result < 60 || result > INT_MAX)
		return (ft_putstr_fd(E_T_SLEEP, 2), false);
	sys->sleep_time = (int)result;
	return (true);
}

bool	sys_init(t_sys *sys, int ac, char **av)
{
	long long	result;
	size_t		start_time;

	if (!sys_init_check(sys, ac, av))
		return (false);
	if (ac == 6)
	{
		result = ft_atoll(av[5]);
		if (result < 1 || result > INT_MAX)
		{
			ft_putstr_fd(E_N_EAT_1, 2);
			return (ft_putstr_fd(E_N_EAT_2, 2), false);
		}
		sys->n_eat = (int)result;
	}
	else
		sys->n_eat = -1;
	sys->end = false;
	sys->start_time = get_time() + (sys->n_philo * 2 * 10);
	pthread_mutex_init(&sys->printf_mutex, NULL);
	pthread_mutex_init(&sys->sync_mutex, NULL);
	return (true);
}

bool	philo_init(t_sys *sys)
{
	int		i;

	i = 0;
	while (i < sys->n_philo)
	{
		pthread_mutex_init(&sys->forks[i], NULL);
		sys->philo[i].id = i;
		sys->philo[i].sys = sys;
		sys->philo[i].left = &sys->forks[i];
		sys->philo[i].right = &sys->forks[(i + 1) % sys->n_philo];
		sys->philo[i].take_left = false;
		sys->philo[i].take_right = false;
		sys->philo[i].sleep_time = sys->sleep_time;
		sys->philo[i].eat_time = sys->eat_time;
		sys->philo[i].last_meal = sys->start_time;
		sys->philo[i].start_time = sys->start_time;
		sys->philo[i].n_philo = sys->n_philo;
		sys->philo[i].eat_count = 0;
		i++;
	}
	return (true);
}

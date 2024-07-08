/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:52:30 by edegraev          #+#    #+#             */
/*   Updated: 2024/07/04 10:08:16 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_sys	t_sys;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_sys			*sys;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	bool			take_left;
	bool			take_right;
	int				sleep_time;
	int				eat_time;
	int				eat_count;
	size_t			last_meal;
	size_t			start_time;
	int				n_philo;
}	t_philo;

typedef struct s_sys
{
	t_philo			philo[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	sync_mutex;
	pthread_t		monitor;
	bool			end;
	int				time_to_die;
	int				sleep_time;
	int				eat_time;
	size_t			start_time;
	int				n_eat;
	int				n_philo;
}	t_sys;

// atoll.c
long long	ft_atoll(const char *str);

// ft.c
int			ft_strlen(char *s);
int			ft_putstr_fd(char *s, int fd);

// init.c
bool		sys_init(t_sys *sys, int ac, char **av);
bool		philo_init(t_sys *sys);

// main.c
bool		is_end(t_philo *philo);

// monitor.c
void		*monitor_routine(t_sys *sys);

// philo.c
void		*routine(t_philo *philo);

// time.c
size_t		get_time(void);
void		ft_usleep(size_t milliseconds);
void		await(t_philo *philo, int nb_philo, int time_to_eat);
void		routine_start_delay(t_philo *philo);

// utils.c
void		printf_mutex(t_sys *sys, t_philo *philo, char *str);
bool		set_end(t_sys *sys);

#endif

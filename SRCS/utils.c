/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:20:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/25 12:13:06 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork);
		philo->l_fork_i = 0;
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		*philo->r_fork_i = 0;
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		*philo->r_fork_i = 0;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_lock(&philo->l_fork);
		philo->l_fork_i = 0;
		pthread_mutex_unlock(&philo->l_fork);
	}
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->pause);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->pause);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->pause);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		error_display(TIME_ERR);
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	odd_wait(t_data *data)
{
	long long	wait;

	wait = data->tt_die - data->tt_eat - data->tt_sleep;
	if (wait < 0)
		wait = -wait;
	if (wait == 0)
		wait = 100;
	return (wait);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->philo[i].l_fork);
	pthread_mutex_destroy(&data->pause);
}

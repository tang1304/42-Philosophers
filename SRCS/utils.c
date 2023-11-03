/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:20:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/08/04 08:30:25 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	check_fork(t_philo *philo, int fork)
{
	long long	time;

	pthread_mutex_lock(&philo->data->forks[fork]);
	if (philo->data->forks_id[fork] == 0)
	{
		philo->data->forks_id[fork] = 1;
		time = get_time() - philo->data->start;
		printf("%lld %d has taken a fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->data->forks[fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->forks[fork]);
	return (0);
}

int	get_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (left == 0 || right == 0)
	{
		if (is_dead(philo) == 1)
			return (0);
		if (left == 0)
			left = check_fork(philo, philo->l_fork);
		if (right == 0)
			right = check_fork(philo, philo->r_fork);
		usleep(500);
	}
	return (1);
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

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->pause);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:04:29 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/14 11:15:57 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	get_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fork) != 0)
		return (0);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (0);
	return (1);
}

int	think(t_philo *philo)
{
	long long	time;

	if (philo->data->death == 1)
		return (0);
	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start;
	if (philo->data->death == 0)
		printf("%lld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	long long	time;

	if (philo->data->death == 1)
		return (0);
	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start;
	if (philo->data->death == 0)
		printf("%lld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data->tt_sleep);
	return (1);
}

static int	eat(t_philo *philo)
{
	long long	time;

	if (philo->data->death == 1)
		return (0);
	if (philo->meals == philo->data->eat_x_times)
		return (0);
	if (!get_forks(philo))
		return (0);
	if (philo->data->death == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		time = get_time() - philo->data->start;
		printf("%lld %d has taken a fork\n", time, philo->id);
		printf("%lld %d has taken a fork\n", time, philo->id);
		printf("%lld %d is eating\n", time, philo->id);
		philo->ate = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo->data->tt_eat);
	}
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

void	action(t_philo *philo, t_data *data)
{
	while (philo->meals != data->eat_x_times && data->death == 0)
	{
		if (!think(philo))
			return ;
		if (!eat(philo))
			return ;
		if (philo->meals == data->eat_x_times)
			break ;
		if (!sleeping(philo))
			return ;
	}
	if (philo->meals == data->eat_x_times)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("Philo %d is done eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
}

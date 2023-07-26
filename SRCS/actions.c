/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:04:29 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/26 09:10:14 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// static int	get_forks(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		if (pthread_mutex_lock(&philo->l_fork) != 0)
// 			return (0);
// 		if (pthread_mutex_lock(philo->r_fork) != 0)
// 		{
// 			pthread_mutex_unlock(&philo->l_fork);
// 			return (0);
// 		}
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->r_fork);
// 		if (pthread_mutex_lock(&philo->l_fork) != 0)
// 		{
// 			pthread_mutex_unlock(philo->r_fork);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

static int	get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		while (pthread_mutex_lock(&philo->l_fork) != 0)
		{
			ft_usleep(1);
		}
		while (pthread_mutex_lock(philo->r_fork) != 0)
			ft_usleep(1);
	}
	else
	{
		while (pthread_mutex_lock(philo->r_fork) != 0)
			ft_usleep(1);
		while (pthread_mutex_lock(&philo->l_fork) != 0)
			ft_usleep(1);
	}
	return (1);
}

int	think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->pause);
	time = get_time() - philo->data->start;
	if (philo->data->death == 0)
		printf("%lld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->pause);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->pause);
	time = get_time() - philo->data->start;
	if (philo->data->death == 0)
		printf("%lld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->pause);
	ft_usleep(philo->data->tt_sleep);
	return (1);
}

static int	eat(t_philo *philo)
{
	long long	time;

	get_forks(philo);
	if (is_dead(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->pause);
		time = get_time() - philo->data->start;
		printf("%lld %d has taken a fork\n", time, philo->id);
		printf("%lld %d has taken a fork\n", time, philo->id);
		printf("%lld %d is eating\n", time, philo->id);
		philo->ate = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->data->pause);
		ft_usleep(philo->data->tt_eat);
	}
	release_forks(philo);
	return (1);
}

void	action(t_philo *philo, t_data *data)
{
	// long long	wait;

	// pthread_mutex_lock(&philo->data->pause);
	// wait = odd_wait(data);
	// pthread_mutex_unlock(&philo->data->pause);
	while (philo->meals != data->eat_x_times)
	{
		think(philo);
		// if (philo->philo_nbr % 2 != 0 && philo->id % 2 != 0)
		// 	ft_usleep(50);
		if (is_dead(philo) == 1)
			return ;
		eat(philo);
		if (philo->meals == data->eat_x_times)
			break ;
		sleeping(philo);
		usleep(10 * philo->philo_nbr);
	}
	if (philo->meals == data->eat_x_times)
	{
		pthread_mutex_lock(&philo->data->pause);
		printf("Philo %d is done eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->pause);
	}
}

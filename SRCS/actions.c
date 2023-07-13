/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:04:29 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/13 15:15:40 by tgellon          ###   ########lyon.fr   */
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

	// if (!check_death(philo))
	// 	return (0);
	// pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start;
	if (philo->data->death == 0)
		printf("%lld %d is thinking\n", time, philo->id);
	// pthread_mutex_unlock(&philo->data->write);
	// if (!check_death(philo))
	// 	return (0);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	long long	time;

	// if (!check_other_death(philo))
	// 	return (0);
	// pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start;
	if (philo->data->death == 0)
		printf("%lld %d is sleeping\n", time, philo->id);
	// pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data->tt_sleep, philo);
	// if (!check_death(philo))
	// 	return (0);
	return (1);
}

static int	eat(t_philo *philo)
{
	long long	time;

	// if (!check_death(philo))
	// 	return (0);
	if (philo->meals == philo->data->eat_x_times)
		return (0);
	if (!get_forks(philo))
		return (0);
	// if (!check_death(philo))
	// 	return (0);
	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start;
	printf("%lld %d has taken a fork\n", time, philo->id);
	printf("%lld %d has taken a fork\n", time, philo->id);
	printf("%lld %d is eating\n", time, philo->id);
	philo->ate = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data->tt_eat, philo);
	// if (!check_own_death(philo))
	// 	return (0);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

void	action(t_philo *philo, t_data *data)
{
	while (philo->meals != data->eat_x_times && data->death == 0)
	{
		// if (!check_own_death(philo))
		// 	return ;
		if (!think(philo))
			return ;
		if (!eat(philo))
			return ;
		if (!sleeping(philo))
			return ;
	}
	if (philo->meals == data->eat_x_times)
		printf("Philo %d is done eating\n", philo->id);
}

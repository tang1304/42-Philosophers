/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:04:29 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/26 16:07:43 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	release_forks(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->forks[fork]);
	philo->data->forks_id[fork] = 0;
	pthread_mutex_unlock(&philo->data->forks[fork]);
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
	usleep(philo->data->tt_sleep * 1000);
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
		printf("%lld %d is eating\n", time, philo->id);
		philo->ate = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->data->pause);
		usleep(philo->data->tt_eat * 1000);
	}
	release_forks(philo, philo->l_fork);
	release_forks(philo, philo->r_fork);
	return (1);
}

void	action(t_philo *philo, t_data *data)
{
	while (philo->meals != data->eat_x_times)
	{
		think(philo);
		if (is_dead(philo) == 1)
			return ;
		eat(philo);
		if (philo->meals == data->eat_x_times)
			break ;
		sleeping(philo);
	}
	if (philo->meals == data->eat_x_times)
	{
		pthread_mutex_lock(&philo->data->pause);
		printf("Philo %d is done eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->pause);
	}
}

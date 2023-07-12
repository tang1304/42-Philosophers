/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:20:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/11 14:58:09 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_death(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start;
	if ((get_time() - philo->ate) >= philo->data->tt_die)
	{
		printf("%lld Philo %d is dead\n", time, philo->id);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->data->write);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->write);
	return (1);
	// pthread_mutex_lock(&philo->data->write);
	// if (philo->data->dead)
	// {
	// 	pthread_mutex_unlock(&philo->data->write);
	// 	return (1);
	// }
	// pthread_mutex_unlock(&philo->data->write);
	// return (0);
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

void	ft_usleep(long long waiting)
{
	long	time;

	time = get_time();
	usleep(time * 900);
	while (get_time() - time < waiting)
		usleep(100);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->philo[i].l_fork);
	pthread_mutex_destroy(&data->write);
}

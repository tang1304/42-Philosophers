/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:20:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/18 08:25:59 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->write);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->write);
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

void	ft_usleep(long long waiting)
{
	long long	time;

	time = get_time();
	while ((get_time() - time) < waiting)
		usleep(200);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->philo[i].l_fork);
	pthread_mutex_destroy(&data->write);
}

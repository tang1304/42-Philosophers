/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:20:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/30 12:13:35 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->dead)
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
		return (TIME_ERR);
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
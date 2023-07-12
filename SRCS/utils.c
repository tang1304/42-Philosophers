/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:20:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/12 15:47:36 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_death(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write);
	if (philo->data->death == 1)
		return (0);
	time = get_time() - philo->ate;
	// printf("Philo %d time last meal: %lld\n", philo->id, philo->ate);
	printf("Philo %d time: %lld\n", philo->id, time);
	if (time >= philo->data->tt_die)
	{
		printf("%lld Philo %d is dead\n", (get_time() - philo->data->start), philo->id);
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->write);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->write);
	return (1);
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
		usleep(100);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->philo[i].l_fork);
	pthread_mutex_destroy(&data->write);
}

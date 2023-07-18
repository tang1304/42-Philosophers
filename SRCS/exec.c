/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:15:53 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/18 08:53:47 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	handle_one_philo(t_philo *philo)
{
	printf("%lld Philo %d is thinking ...\n", get_time() - \
			philo->data->start, philo->id);
	printf("%lld Philo %d has taken a fork\n", get_time() - \
			philo->data->start, philo->id);
	printf("%lld Philo %d has died\n", get_time() - philo->data->start, \
			philo->id);
}

static int	check_death(t_philo *philo)
{
	long long	time;

	// pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->ate;
	if (time >= philo->data->tt_die && philo->data->death == 0)
	{
		printf("%lld %d died\n", (get_time() - philo->data->start), philo->id);
		philo->data->death = 1;
		// pthread_mutex_unlock(&philo->data->write);
		return (0);
	}
	if (philo->data->death == 1)
	{
		// pthread_mutex_unlock(&philo->data->write);
		return (0);
	}
	// pthread_mutex_unlock(&philo->data->write);
	return (1);
}

static int	death_check_loop(t_data *data)
{
	int	i;

	while (1)
	{
		ft_usleep(2);
		i = -1;
		while (++i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->write);
			if (data->philo->meals == data->eat_x_times)
			{
				pthread_mutex_unlock(&data->write);
				return (1);
			}
			if (data->philo[i].ate != 0)
			{
				if (!check_death(&data->philo[i]))
				{
					pthread_mutex_unlock(&data->write);
					return (0);
				}
			}
			pthread_mutex_unlock(&data->write);
		}
	}
}

int	threads_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->write);
	while (++i < data->philo_nbr)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, \
			&data->philo[i]) != 0)
			return (free(data->philo), error_display(TRHREAD_CR), \
					pthread_mutex_unlock(&data->write), 0);
	}
	pthread_mutex_unlock(&data->write);
	pthread_mutex_lock(&data->write);
	data->start = get_time();
	pthread_mutex_unlock(&data->write);
	i = -1;
	death_check_loop(data);
	while (++i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(data->philo), error_display(THR_JOIN), 0);
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->write);
	while (philo->data->start == 0)
		continue ;
	philo->ate = get_time();
	pthread_mutex_unlock(&philo->data->write);
	if (philo->id % 2 == 0)
		ft_usleep(2);
	if (philo->data->philo_nbr == 1)
		return (handle_one_philo(philo), NULL);
	action(philo, philo->data);
	return (NULL);
}

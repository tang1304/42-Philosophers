/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:15:53 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/13 10:39:11 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	threads_init(t_data *data)
{
	int	i;

	i = -1;
	// pthread_mutex_lock(&data->write);
	while (++i < data->philo_nbr)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, \
			&data->philo[i]) != 0)
			return (free(data->philo), error_display(TRHREAD_CR), 0);
	}
	// pthread_mutex_unlock(&data->write);
	pthread_mutex_lock(&data->write);
	data->start = get_time();
	pthread_mutex_unlock(&data->write);
	i = -1;
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
	long long	start;

	philo = (t_philo *)arg;
	while (philo->data->start == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		start = philo->data->start;
		pthread_mutex_unlock(&philo->data->write);
	}
	philo->ate = get_time();
	if (philo->id % 2 == 0)
		usleep(500);
	if (philo->data->philo_nbr == 1)
		return (printf("%lld Philo %d is thinking ...\n", get_time() - \
						philo->data->start, philo->id), NULL);
	action(philo, philo->data);
	return (NULL);
}

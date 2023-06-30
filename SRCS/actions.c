/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:04:29 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/30 14:52:34 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start;
	printf("%lld Philo %d is thinking ...\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
	return (1);
}


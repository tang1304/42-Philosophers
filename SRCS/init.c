/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:22:14 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/26 08:36:33 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->philo[i].l_fork, NULL) != 0)
			return (free(data->philo), 0);
		data->philo[i].philo_nbr = data->philo_nbr;
		data->philo[i].id = i + 1;
		data->philo[i].tt_eat = data->tt_eat;
		data->philo[i].tt_sleep = data->tt_sleep;
		data->philo[i].ate = 0;
		data->philo[i].meals = 0;
		data->philo[i].dead = 0;
		data->philo[i].data = data;
		data->philo[i].l_fork_i = 0;
		if (i == data->philo_nbr - 1)
			data->philo[i].r_fork_i = &data->philo[0].l_fork_i;
		else
			data->philo[i].r_fork_i = &data->philo[i + 1].l_fork_i;
		data->philo[i].r_fork = &data->philo[(i + 1) % data->philo_nbr].l_fork;
	}
	return (1);
}

static int	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->pause, NULL) != 0)
		return (error_display(MUTEX), free(data->philo), 0);
	return (1);
}

int	data_init(t_data *data, char **argv)
{
	int	i;

	data->philo_nbr = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_x_times = ft_atoi(argv[5]);
	else
		data->eat_x_times = -1;
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (error_display(MALLOC), 0);
	i = -1;
	if (!philo_init(data))
		return (0);
	if (!mutex_init(data))
		return (0);
	return (1);
}

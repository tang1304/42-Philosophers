/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:22:14 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/14 09:57:49 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
	while (++i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->philo[i].l_fork, NULL) != 0)
			return (free(data->philo), 0);
		data->philo[i].id = i + 1;
		data->philo[i].ate = 0;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		data->philo[i].r_fork = &data->philo[(i + 1) % data->philo_nbr].l_fork;
	}
	return (1);
}

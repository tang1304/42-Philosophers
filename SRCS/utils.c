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

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (TIME_ERR);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

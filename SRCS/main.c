/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:13:10 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/11 14:38:52 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (error_check(argc, argv))
		return (1);
	ft_bzero(&data, sizeof(t_data));
	if (!data_init(&data, argv))
		return (1);
	threads_init(&data);
	destroy_mutexes(&data);
}

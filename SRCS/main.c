/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:13:10 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/30 10:24:29 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (error_check(argc, argv))
		return (1);
	ft_bzero(&data, sizeof(t_data));
	if (!data_init(&data, argc, argv))
		return (1);
	threads_init(&data);
}

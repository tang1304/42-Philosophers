/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:13:10 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/29 11:56:56 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (error_check(argc, argv))
		return (0);
	ft_bzero(&data, sizeof(t_data));
	data_init(&data, argc, argv);
	threads_init(&data);
}

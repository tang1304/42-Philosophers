/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:25:24 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/28 10:45:38 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	error_display(char *msg)
{
	printf("%s\n", msg);
	return ;
}

int	error_check(int argc, char **argv)
{
	int	nbr;
	int	i;

	if (argc != 5 && argc != 6)
	{
		error_display("Error: Wrong number of arguments");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		nbr = ft_atoi(argv[i]);
		if (nbr <= 0)
		{
			error_display("Error: Bad argument, must be a positive number");
			return (1);
		}
	}
	return (0);
}
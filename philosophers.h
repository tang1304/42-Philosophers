/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:54:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/29 13:30:35 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "../libft/libft.h"
# include <sys/time.h>
# include <pthread.h>

# define MALLOC "Error: Malloc failure"
# define TRHREAD_CR "Error: pthread_create failure"

typedef struct s_data
{
	int			philo_nbr;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			eat_x_times;
	t_philo		*philo;
}				t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	int				alive;
	int				ate;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philo;

/*	main.c	*/
int		main(int argc, char **argv);

/*	errors.c	*/
int		error_check(int argc, char **argv);
void	error_display(char *msg);

/*	exec.c	*/
void	*philo_routine(void *arg);

/*	init.c	*/
void	data_init(t_data *data, int argc, char **argv);
void	threads_init(t_data *data);

#endif

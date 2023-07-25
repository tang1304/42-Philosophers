/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:54:45 by tgellon           #+#    #+#             */
/*   Updated: 2023/07/25 10:57:31 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>

# define MALLOC "Error: Malloc failure"
# define TRHREAD_CR "Error: pthread_create failure"
# define TIME_ERR "Error: gettimeofday failure"
# define THR_JOIN "Error: pthread_join failure\n"

typedef struct s_data
{
	int				philo_nbr;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				death;
	int				eat_x_times;
	long long		start;
	pthread_mutex_t	pause;
	struct s_philo	*philo;
}				t_data;

typedef struct s_philo
{
	t_data			*data;
	int				philo_nbr;
	int				id;
	int				tt_eat;
	int				tt_sleep;
	long long		ate;
	int				meals;
	int				dead;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	// int				l_fork_i;
	pthread_mutex_t	*r_fork;
	// int				*r_fork_i;
}				t_philo;

/*	main.c	*/
int			main(int argc, char **argv);

/*	actions	*/
void		action(t_philo *philo, t_data *data);
int			think(t_philo *philo);

/*	errors.c	*/
int			error_check(int argc, char **argv);
void		error_display(char *msg);

/*	exec.c	*/
int			threads_init(t_data *data);
void		*philo_routine(void *arg);

/*	init.c	*/
int			data_init(t_data *data, char **argv);

/*	lib.c	*/
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		ft_usleep(long long waiting);

/*	utils.c	*/
void		release_forks(t_philo *philo);
int			is_dead(t_philo *philo);
long long	get_time(void);
long long	odd_wait(t_data *data);
void		destroy_mutexes(t_data *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 09:18:55 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/11/26 10:55:52 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//memset
# include <string.h>
//printf
# include <stdio.h>
//malloc
# include <stdlib.h>
//write, usleep,
# include <unistd.h>
//gettimeofday
# include <sys/time.h>
//pthread functions
# include <pthread.h>
//data types
# include <sys/types.h>
//uint64_t
# include <stddef.h>

//structure to handle death
typedef struct s_death
{
	int				status;
	pthread_mutex_t	lock_death;
}				t_death;

//main data struct with shared vars
typedef struct s_data
{
	int				n_philos;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				n_meals;
	u_int64_t		start;
	pthread_mutex_t	print;
	t_death			death;
}		t_data;

//struct to handle forks and their status
typedef struct s_forks
{
	int				status;
	pthread_mutex_t	fork;
}				t_forks;

//main philo struct
typedef struct s_philo
{
	t_data			*data;
	t_forks			*forks;
	pthread_t		philo;
	int				n_philos;
	int				id;
	int				times_eaten;
	int				n_meals;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		last_ate;
}				t_philo;

//actions
void	print_action(t_philo *philo, char *action);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	*routine(void *philo_data);
//exit
void	ft_exit(t_philo *philo, t_forks *forks);
//init
void	set_args(int argc, char **argv, t_data *data);
void	init_data(t_data *data);
t_forks	*init_forks(t_data *data);
void	init_philos(t_data *data, t_philo *philo, t_forks *forks);
//lock
int		check_first(t_philo *philo);
int		check_second(t_philo *philo);
void	lock_fork(t_philo *philo, t_forks *fork);
void	unlock_fork(t_philo *philo, t_forks *fork);
//main
t_data	*data(void);
int		create_threads(t_philo *philo);
int		main(int argc, char **argv);
//monitor
int		is_dead(t_philo *philo);
int		check_death(t_philo *philo);
void	wait_and_check(t_philo *philo, u_int64_t time);
//utils
int		ft_atoi(char *str);
int		check_numbers(char **argv);
int		check_args(int argc, char **argv);
size_t	get_time(void);
void	ft_usleep(u_int64_t time);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:42:48 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/11/26 11:42:54 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (i == 1)
			data->n_philos = ft_atoi(argv[i]);
		if (i == 2)
			data->time_to_die = ft_atoi(argv[i]);
		if (i == 3)
			data->time_to_eat = ft_atoi(argv[i]);
		if (i == 4)
			data->time_to_sleep = ft_atoi(argv[i]);
		i++;
	}
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	else
		data->n_meals = -1;
}

void	init_data(t_data *data)
{
	t_death	death;

	death.status = 0;
	pthread_mutex_init(&death.lock_death, NULL);
	data->start = get_time();
	data->death = death;
	pthread_mutex_init(&data->print, NULL);
}

t_forks	*init_forks(t_data *data)
{
	t_forks	*forks;
	int		i;

	i = 0;
	forks = malloc(sizeof(t_forks) * data->n_philos);
	if (!forks)
	{
		printf("Failed to allocate memory for forks\n");
		return (NULL);
	}
	while (i < data->n_philos)
	{
		forks[i].status = 1;
		if (pthread_mutex_init(&forks[i].fork, NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

void	init_philos(t_data *data, t_philo *philo, t_forks *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		philo[i].n_philos = data->n_philos;
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].forks = forks;
		philo[i].data = data;
		philo[i].last_ate = get_time();
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].n_meals = data->n_meals;
		i++;
	}
}

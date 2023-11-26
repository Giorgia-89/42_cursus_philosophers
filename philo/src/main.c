/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 09:21:30 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/11/26 10:54:01 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philos)
	{
		if (pthread_create(&philo[i].philo, NULL, &routine, &philo[i]))
		{
			printf("Failed to create thread\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo->n_philos)
	{
		if (pthread_join(philo[i].philo, NULL))
		{
			printf("Failed to join thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_forks	*forks;

	if (check_args(argc, argv) < 1)
		return (0);
	set_args(argc, argv, data());
	if (data()->n_meals != 0)
	{
		init_data(data());
		forks = init_forks(data());
		if (!forks)
			return (1);
		philo = malloc(sizeof(t_philo) * data()->n_philos);
		if (!philo)
		{
			printf("Failed to allocate memory for philos\n");
			ft_exit(NULL, forks);
			return (1);
		}
		init_philos(data(), philo, forks);
		if (!create_threads(philo))
			ft_exit(philo, forks);
	}
	return (0);
}

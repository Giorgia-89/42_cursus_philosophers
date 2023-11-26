/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 09:33:38 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/11/26 10:50:14 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_exit(t_philo *philo, t_forks *forks)
{
	int	i;

	i = 0;
	if (forks)
	{
		while (i < data()->n_philos)
		{
			pthread_mutex_destroy(&forks[i].fork);
			i++;
		}
		free(forks);
	}
	i = 0;
	if (philo)
	{
		pthread_mutex_destroy(&data()->print);
		pthread_mutex_destroy(&data()->death.lock_death);
		free(philo);
	}
	return ;
}

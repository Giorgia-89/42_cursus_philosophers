/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:03:00 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/11/26 10:52:51 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_first(t_philo *philo)
{
	if (philo->id == 1)
		return (philo->n_philos - 1);
	else
		return (philo->id - 1);
}

int	check_second(t_philo *philo)
{
	if (philo->id == 1)
		return (philo->id - 1);
	else
		return (philo->id - 2);
}

void	lock_fork(t_philo *philo, t_forks *fork)
{
	while (!check_death(philo))
	{
		pthread_mutex_lock(&fork->fork);
		if (fork->status == 1)
		{
			fork->status = 0;
			pthread_mutex_unlock(&fork->fork);
			print_action(philo, "has taken a fork");
			break ;
		}
		else
			pthread_mutex_unlock(&fork->fork);
	}
}

void	unlock_fork(t_philo *philo, t_forks *fork)
{
	while (!check_death(philo))
	{
		pthread_mutex_lock(&fork->fork);
		if (fork->status == 0)
		{
			fork->status = 1;
			pthread_mutex_unlock(&fork->fork);
			break ;
		}
		else
			pthread_mutex_unlock(&fork->fork);
	}
}

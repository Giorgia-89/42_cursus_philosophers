/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 09:53:10 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/11/26 10:54:57 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death.lock_death);
	if (philo->data->death.status == 1)
	{
		pthread_mutex_unlock(&philo->data->death.lock_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death.lock_death);
	return (0);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death.lock_death);
	if (get_time() - philo->last_ate >= philo->time_to_die)
	{
		if (philo->data->death.status == 1)
		{
			pthread_mutex_unlock(&philo->data->death.lock_death);
			return (1);
		}
		pthread_mutex_lock(&philo->data->print);
		printf("\033[0;31m%zu %d died\n\033[0m", get_time() - \
		philo->data->start, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		philo->data->death.status = 1;
		pthread_mutex_unlock(&philo->data->death.lock_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death.lock_death);
	return (0);
}

void	wait_and_check(t_philo *philo, u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (check_death(philo))
			return ;
		ft_usleep(time / 10);
	}
	check_death(philo);
}

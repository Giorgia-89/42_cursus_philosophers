/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 09:46:55 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/11/26 10:49:52 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->death.lock_death);
	if (philo->data->death.status == 1)
	{
		pthread_mutex_unlock(&philo->data->death.lock_death);
		return ;
	}
	pthread_mutex_lock(&philo->data->print);
	printf("%zu %d %s\n", get_time() - philo->data->start, philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->death.lock_death);
}

void	ft_eat(t_philo *philo)
{
	int	first;
	int	second;

	first = check_first(philo);
	second = check_second(philo);
	lock_fork(philo, &philo->forks[first]);
	lock_fork(philo, &philo->forks[second]);
	if (is_dead(philo))
		return ;
	print_action(philo, "is eating");
	philo->last_ate = get_time();
	wait_and_check(philo, philo->time_to_eat);
	unlock_fork(philo, &philo->forks[first]);
	unlock_fork(philo, &philo->forks[second]);
	philo->times_eaten++;
	return ;
}

void	ft_sleep(t_philo *philo)
{
	if (philo->times_eaten < philo->n_meals || philo->n_meals == -1)
	{
		print_action(philo, "is sleeping");
		wait_and_check(philo, philo->time_to_sleep);
	}
}

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	philo->last_ate = get_time();
	if (philo->n_philos % 2 != 0 && philo->id == philo->n_philos)
		print_action(philo, "is thinking");
	if (philo->id % 2 == 0)
	{
		print_action(philo, "is thinking");
		wait_and_check(philo, philo->time_to_eat);
	}
	while (philo->times_eaten < philo->n_meals || philo->n_meals == -1)
	{
		ft_eat(philo);
		if (is_dead(philo))
			return (NULL);
		ft_sleep(philo);
		usleep(1000);
		if (is_dead(philo))
			return (NULL);
		if (philo->times_eaten < philo->n_meals || philo->n_meals == -1)
			print_action(philo, "is thinking");
	}
	return (NULL);
}

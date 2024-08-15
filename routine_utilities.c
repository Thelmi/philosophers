/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:17 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/15 00:52:53 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000LL) + (now.tv_usec / 1000));
}

int	one_philo(t_philo **philo, double timestamp_in_ms)
{
	long long	started_meal;

	started_meal = time_now() - (*philo)->info->time_bc;
	while ((int)((time_now() - (*philo)->info->time_bc)
		- started_meal) < ((*philo)->info->t2die))
	{
		usleep(150);
	}
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	pthread_mutex_lock(&(*philo)->info->print_lock);
	printf("%d %d died\n", (int)timestamp_in_ms, (*philo)->philo);
	pthread_mutex_unlock(&(*philo)->info->print_lock);
	return (1);
}

int	dead_philo(t_philo **philo, double timestamp_in_ms)
{
	pthread_mutex_lock(&(*philo)->info->death_lock);
	if ((*philo)->info->dead == 1)
	{
		pthread_mutex_unlock(&(*philo)->info->death_lock);
		return (1);
	}
	(*philo)->info->dead = 1;
	pthread_mutex_unlock(&(*philo)->info->death_lock);
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	pthread_mutex_lock(&(*philo)->info->print_lock);
	printf("%d %d died\n", (int)timestamp_in_ms, (*philo)->philo);
	pthread_mutex_unlock(&(*philo)->info->print_lock);
	return (1);
}

int	death_check(t_philo **philo, double timestamp_in_ms)
{
	if ((*philo)->info->philos == 1)
	{
		one_philo(philo, timestamp_in_ms);
		return (1);
	}
	pthread_mutex_lock(&(*philo)->info->death_lock);
	if ((*philo)->info->dead == 1)
	{
		pthread_mutex_unlock(&(*philo)->info->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->info->death_lock);
	if ((time_now() - (*philo)->info->time_bc)
		- (*philo)->last_meal >= (*philo)->info->t2die)
	{
		dead_philo(philo, timestamp_in_ms);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:17 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/15 02:15:01 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_check(t_philo **philo, int *fork1, int *fork2)
{
	int	temp;

	if ((*philo)->philo == 1)
	{
		(*fork1) = (*philo)->info->philos - 1;
		(*fork2) = (*philo)->philo - 1;
	}
	else
	{
		(*fork1) = (*philo)->philo - 2;
		(*fork2) = (*philo)->philo - 1;
	}
	if ((*fork1) > (*fork2))
	{
		temp = (*fork1);
		(*fork1) = (*fork2);
		(*fork2) = temp;
	}
}

int	eating_check(t_philo **philo, double timestamp_in_ms)
{
	long long	started_meal;

	started_meal = 0;
	if (death_check(philo, timestamp_in_ms))
		return (1);
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	pthread_mutex_lock(&(*philo)->info->print_lock);
	printf("%s%d %s%d %shas taken a fork\n", CYAN,
		(int)timestamp_in_ms, RED, (*philo)->philo, RESET);
	printf("%s%d %s%d %shas taken a fork\n", CYAN,
		(int)timestamp_in_ms, RED, (*philo)->philo, RESET);
	printf("%s%d %s%d %sis eating\n", CYAN,
		(int)timestamp_in_ms, RED, (*philo)->philo, RESET);
	pthread_mutex_unlock(&(*philo)->info->print_lock);
	started_meal = time_now() - (*philo)->info->time_bc;
	while ((int)((time_now() - (*philo)->info->time_bc)
		- started_meal) < ((*philo)->info->t2eat))
	{
		if (death_check(philo, timestamp_in_ms))
			return (1);
		usleep(150);
	}
	return (0);
}

int	eating_routine(t_philo **philo, double timestamp_in_ms,
	int fork1, int fork2)
{
	(*philo)->info->forks[fork1] = (*philo)->philo;
	(*philo)->info->forks[fork2] = (*philo)->philo;
	if (eating_check(philo, timestamp_in_ms))
	{
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
		return (1);
	}
	(*philo)->last_meal = time_now() - (*philo)->info->time_bc;
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
	pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
	if (death_check(philo, timestamp_in_ms))
		return (1);
	return (0);
}

int	eating(t_philo **philo, double timestamp_in_ms)
{
	int	fork1;
	int	fork2;

	fork1 = 0;
	fork2 = 0;
	while (1)
	{
		if (death_check(philo, timestamp_in_ms))
			return (1);
		fork_check(philo, &fork1, &fork2);
		pthread_mutex_lock(&(*philo)->info->fork_lock[fork1]);
		pthread_mutex_lock(&(*philo)->info->fork_lock[fork2]);
		if ((*philo)->info->forks[fork2] != (*philo)->philo
			&& (*philo)->info->forks[fork1] != (*philo)->philo)
		{
			if (eating_routine(philo, timestamp_in_ms, fork1, fork2))
				return (1);
			break ;
		}
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
	}
	if (death_check(philo, timestamp_in_ms))
		return (1);
	return (0);
}

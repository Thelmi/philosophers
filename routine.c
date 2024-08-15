/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:17 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/15 16:29:54 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo **philo, double timestamp_in_ms)
{
	if (death_check(philo, timestamp_in_ms))
		return (1);
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	pthread_mutex_lock(&(*philo)->info->print_lock);
	printf("%s%d %s%d %sis sleeping\n", CYAN,
		(int)timestamp_in_ms, RED, (*philo)->philo, RESET);
	pthread_mutex_unlock(&(*philo)->info->print_lock);
	(*philo)->started_sleep = time_now() - (*philo)->info->time_bc;
	while ((time_now() - (*philo)->info->time_bc)
		- (*philo)->started_sleep < ((*philo)->info->t2sleep))
	{
		usleep(150);
		if (death_check(philo, timestamp_in_ms))
			return (1);
	}
	return (0);
}

int	thinking(t_philo **philo, double timestamp_in_ms)
{
	if (death_check(philo, timestamp_in_ms))
		return (1);
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	pthread_mutex_lock(&(*philo)->info->print_lock);
	printf("%s%d %s%d %sis thinking\n", CYAN,
		(int)timestamp_in_ms, RED, (*philo)->philo, RESET);
	pthread_mutex_unlock(&(*philo)->info->print_lock);
	return (0);
}

int	specified_meals(t_philo *philo, long long timestamp_in_ms)
{
	int	i;

	i = 0;
	while (i < philo->info->meals)
	{
		if (eating(&philo, timestamp_in_ms))
		{
			if (philo)
				free(philo);
			return (1);
		}
		if (i == philo->info->meals - 1)
			break ;
		if (sleeping(&philo, timestamp_in_ms)
			|| thinking(&philo, timestamp_in_ms))
		{
			if (philo)
				free(philo);
			return (1);
		}
		i++;
	}
	return (0);
}

int	no_specified_meals(t_philo *philo, long long timestamp_in_ms)
{
	while (1)
	{
		if (eating(&philo, timestamp_in_ms)
			|| sleeping(&philo, timestamp_in_ms)
			|| thinking(&philo, timestamp_in_ms))
		{
			if (philo)
				free(philo);
			return (1);
		}
	}
	return (0);
}

void	*life(void *philo_num)
{
	long long	timestamp_in_ms;
	t_philo		*philo;

	philo = (t_philo *)philo_num;
	timestamp_in_ms = 0;
	if (philo->info->philos != 1 && philo->philo % 2 == 1)
		usleep (1000);
	if (philo->info->meals != -1)
	{
		if (specified_meals(philo, timestamp_in_ms))
			return (NULL);
	}
	else
	{
		if (no_specified_meals(philo, timestamp_in_ms))
			return (NULL);
	}
	if (philo)
		free(philo);
	return (NULL);
}

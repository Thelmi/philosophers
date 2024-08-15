/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:17 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/09 16:31:30 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initializer(t_philo *philo, t_info *info, int i)
{
	philo->total_meals = 0;
	philo->last_meal = 0;
	philo->philo = i + 1;
	philo->info = info;
}

int	starting_threads(t_info *info, pthread_t threads[200], t_philo *philo)
{
	int	i;

	i = 0;
	philo = NULL;
	while (i < info->philos)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (0);
		initializer(philo, info, i);
		if (pthread_create(&threads[i], NULL, life, (void *)philo))
			return (0);
		i++;
	}
	i = 0;
	while (i < info->philos)
	{
		if (pthread_join(threads[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	execution(t_info *info)
{
	pthread_t	threads[200];
	t_philo		*philo;
	int			i;

	philo = NULL;
	pthread_mutex_init(&info->death_lock, NULL);
	pthread_mutex_init(&info->print_lock, NULL);
	i = 0;
	info->time_bc = time_now();
	while (i < 200)
	{
		pthread_mutex_init(&info->fork_lock[i], NULL);
		i++;
	}
	if (!starting_threads(info, threads, philo))
		return (0);
	i = 0;
	while (i < 200)
	{
		pthread_mutex_destroy(&info->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&info->death_lock);
	pthread_mutex_destroy(&info->print_lock);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (!(parsing(ac, av, &info)))
		return (1);
	if (!(execution(&info)))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:17 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/05 01:32:12 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philo *philo, double timestamp_in_ms)
{
	while (1)
	{
		// printf("xxx %d\n", philo->philo);
		if (philo->philo == 1 && (philo->info->forks[0] != 1
			&& philo->info->forks[philo->info->philos - 1] != 1))
		{
			{
				pthread_mutex_lock(&philo->info->fork_lock[0]);
				pthread_mutex_lock(&philo->info->fork_lock[philo->info->philos - 1]);
				philo->info->forks[0] = 1;
				philo->info->forks[philo->info->philos - 1] = 1;
				printf("%f %d has taken a fork\n", timestamp_in_ms, philo->philo);
				printf("%f %d has taken a fork\n", timestamp_in_ms, philo->philo);
				printf("%f %d is eating\n", timestamp_in_ms, philo->philo);
				// int i = 0;
				// i = 0;
				// while (i < philo->info->philos)
				// {
				// 	printf("%d ", philo->info->forks[i]);
				// 	i++;
				// }
				// printf("\n");
				usleep(philo->info->t2eat * 1000);
				printf("blsa7a %d\n", philo->philo);
				pthread_mutex_unlock(&philo->info->fork_lock[0]);
				pthread_mutex_unlock(&philo->info->fork_lock[philo->info->philos - 1]);
			}
			break ;
		}
		else if ((philo->philo != 1 && philo->info->forks[philo->philo - 1] != philo-> philo
			&& philo->info->forks[philo->philo - 2] != philo-> philo))
		{
			pthread_mutex_lock(&philo->info->fork_lock[philo->philo - 2]);
			pthread_mutex_lock(&philo->info->fork_lock[philo->philo - 1]);
			philo->info->forks[philo->philo - 1] = philo ->philo;
			philo->info->forks[philo->philo - 2] = philo ->philo;
			// int i = 0;
			// i = 0;
			// while (i < philo->info->philos)
			// {
			// 	printf("%d ", philo->info->forks[i]);
			// 	i++;
			// }
			// printf("\n");
			printf("%f %d has taken a fork\n", timestamp_in_ms, philo->philo); // modify the sleep to start from the last meal time (difference) & the begining of the program
			printf("%f %d has taken a fork\n", timestamp_in_ms, philo->philo);
			printf("%f %d is eating\n", timestamp_in_ms, philo->philo);
			usleep(philo->info->t2eat * 1000);
			printf("blsa7a %d\n", philo->philo);
			pthread_mutex_unlock(&philo->info->fork_lock[philo->philo - 1]);
			pthread_mutex_unlock(&philo->info->fork_lock[philo->philo - 2]);
			break ;
		}
	}
	// int i = 0;
	// i = 0;
    // while (i < philo->info->philos)
	// {
	// 	printf("%d ", philo->info->forks[i]);
	// 	i++;
	// }
    // printf("\n");
}

void sleeping(t_philo *philo, double timestamp_in_ms)
{
	pthread_mutex_lock(&philo->info->sleep_lock);
    printf("%f %d is sleeping\n", timestamp_in_ms, philo->philo);
    pthread_mutex_unlock(&philo->info->sleep_lock);
    usleep(philo->info->t2sleep * 1000);
}

void thinking(t_philo *philo, double timestamp_in_ms)
{
	pthread_mutex_lock(&philo->info->think_lock);
    printf("%f %d is thinking\n", timestamp_in_ms, philo->philo);
    pthread_mutex_unlock(&philo->info->think_lock);
}

void *life(void *philo_num)
{
    struct timeval current_time;
    double timestamp_in_ms;
	t_philo *philo;
	philo = (t_philo *)philo_num;

    gettimeofday(&current_time, NULL);
    timestamp_in_ms = current_time.tv_sec * 1000 + (current_time.tv_usec) / 1000;
	int loop = 0;
	while (loop < 5)
	{
		eating(philo, timestamp_in_ms);
		sleeping(philo, timestamp_in_ms);
		thinking(philo, timestamp_in_ms);
		loop++;
	}
    // printf("%f %d died\n", timestamp_in_ms, philo->philo);
	if (philo)
	{
		free(philo);
    }
	return (NULL);	
}

void   initializer(t_philo *philo, t_info *info, int i)
{
    philo->total_meals = 0;
    philo->last_meal = 0;
    philo->philo = i + 1;
    philo->info = info;
}

int    execution(t_info *info)
{
	pthread_t threads[info->philos];
    t_philo *philo;
	int i;

	pthread_mutex_init(&info->think_lock, NULL);
	pthread_mutex_init(&info->sleep_lock, NULL);
	pthread_mutex_init(&info->death_lock, NULL);
	i = 0;
	while (i < 200)
	{
		pthread_mutex_init(&info->fork_lock[i], NULL);
		i++;
	}
	i = 0;
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
	i = 0;
	while (i < 200)
	{
		pthread_mutex_destroy(&info->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&info->think_lock);
	pthread_mutex_destroy(&info->sleep_lock);
	pthread_mutex_destroy(&info->death_lock);
	return (1);
}

int main(int ac, char **av)
{
    t_info info;
    
    if (!(parsing(ac, av, &info)))
        return (1);   
    if (!(execution(&info)))
        return (1);
    return (0);
}

// For tmrw

// eating meals death logic
// correct time printing







// Steps:
// 2. mutex
// 3. routine

// 1. record the program starting time in a variable.

// 2. specify how would you find the time difference to check for the death of a philo & to specify the sleep time. Usleep is in micro sec and the program is in milli sec ***
// 3. specify the logic to follow e.g. even/odd OR monitor etc.
// 4. based on the logic speicify what variables we need to pass/modify/lock in a mutex. Create mutex accordingly.
// 5. check for leak & common cases
// 6. finalized the code
// 7. you can do the bonus if you finish early
// 8. Submit & Cerebrate 🥳🎉


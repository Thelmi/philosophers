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

long long time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000LL) + (now.tv_usec / 1000));
}

int death_check(t_philo **philo, double timestamp_in_ms)
{
	// pthread_mutex_lock(&(*philo)->info->death_lock);
	if ((*philo)->info->dead == 1)
	{
		// pthread_mutex_unlock(&(*philo)->info->death_lock);
		return (1);
	}
	// pthread_mutex_unlock(&(*philo)->info->death_lock);
	if ((time_now() - (*philo)->info->time_bc) - (*philo)->last_meal > (*philo)->info->t2die)
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
		printf("%d %d died\n", (int)timestamp_in_ms, (*philo)->philo);
		return (1);
	}
	return (0);
}

int eating(t_philo **philo, double timestamp_in_ms)
{
	int philo_index = 0;
	long long started_meal = 0;

	while (1)
	{
		if ((*philo)->philo == 1)
			philo_index = (*philo)->info->philos - 1;
		else
			philo_index = (*philo)->philo - 2;
		if (death_check(philo, timestamp_in_ms))
			return (1);
		if (((*philo)->info->forks[(*philo)->philo - 1] != (*philo)-> philo
			&& (*philo)->info->forks[philo_index] != (*philo)-> philo))
		{
			if (death_check(philo, timestamp_in_ms))
				return (1);
			pthread_mutex_lock(&(*philo)->info->fork_lock[(*philo)->philo - 1]);
			pthread_mutex_lock(&(*philo)->info->fork_lock[philo_index]); // modify lock and unlock logic
			if (death_check(philo, timestamp_in_ms))
			{
				pthread_mutex_unlock(&(*philo)->info->fork_lock[philo_index]);
				pthread_mutex_unlock(&(*philo)->info->fork_lock[(*philo)->philo - 1]);
				return (1);
			}
			timestamp_in_ms = time_now() - (*philo)->info->time_bc;
			(*philo)->info->forks[(*philo)->philo - 1] = (*philo)->philo;
			(*philo)->info->forks[philo_index] = (*philo)->philo;
			printf("%s%d %s%d %shas taken a fork\n", CYAN, (int)timestamp_in_ms, RED, (*philo)->philo, RESET); // modify the sleep to start from the last meal time (difference) & the begining of the program
			printf("%s%d %s%d %shas taken a fork\n", CYAN, (int)timestamp_in_ms, RED, (*philo)->philo, RESET);
			printf("%s%d %s%d %sis eating\n", CYAN, (int)timestamp_in_ms, RED, (*philo)->philo, RESET);
			// (*philo)->last_meal = time_now() - (*philo)->info->time_bc;
			// if (death_check(philo, timestamp_in_ms))
			// {
			// 	pthread_mutex_unlock(&(*philo)->info->fork_lock[philo_index]);
			// 	pthread_mutex_unlock(&(*philo)->info->fork_lock[(*philo)->philo - 1]);
			// 	return (1);
			// }
			// usleep(150);
			// printf("xxx %d %d\n", (*philo)->philo, (int)(*philo)->last_meal);
			// printf("xxx %d %d\n", (*philo)->philo, (int)(time_now() - (*philo)->info->time_bc));
			started_meal = time_now() - (*philo)->info->time_bc;
			while((int)((time_now() - (*philo)->info->time_bc) - started_meal) < ((*philo)->info->t2eat))
			{
				// printf("xxxxx%s%d %s%d %sis eating\n", CYAN, (int)timestamp_in_ms, RED, (*philo)->philo, RESET);
				// usleep(150);
				// printf("xxx %d %d\n", (*philo)->philo, (int)((time_now() - (*philo)->info->time_bc) - started_meal));
				if (death_check(philo, timestamp_in_ms))
				{
					pthread_mutex_unlock(&(*philo)->info->fork_lock[philo_index]);
					pthread_mutex_unlock(&(*philo)->info->fork_lock[(*philo)->philo - 1]);
					return (1);
				}
				usleep(150);
			}
			(*philo)->last_meal = time_now() - (*philo)->info->time_bc;
			timestamp_in_ms = time_now() - (*philo)->info->time_bc;
			printf("%s%d blsa7a %d\n", CYAN, (int)timestamp_in_ms, (*philo)->philo);
			pthread_mutex_unlock(&(*philo)->info->fork_lock[philo_index]);
			pthread_mutex_unlock(&(*philo)->info->fork_lock[(*philo)->philo - 1]);
			break ;
		}
	}
	if (death_check(philo, timestamp_in_ms))
		return (1);
    return (0);
}


int sleeping(t_philo **philo, double timestamp_in_ms)
{
	// pthread_mutex_lock(&(*philo)->info->sleep_lock);
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
    printf("%s%d %s%d %sis sleeping\n", CYAN, (int)timestamp_in_ms, RED, (*philo)->philo, RESET);
	(*philo)->started_sleep = time_now() - (*philo)->info->time_bc;
    while((time_now() - (*philo)->info->time_bc) - (*philo)->started_sleep < ((*philo)->info->t2sleep))
	{
		usleep(150);
		if (death_check(philo, timestamp_in_ms))
			return (1);
	}
    // pthread_mutex_unlock(&(*philo)->info->sleep_lock);
	return (0);
}

int thinking(t_philo **philo, double timestamp_in_ms)
{   
	// pthread_mutex_lock(&(*philo)->info->think_lock);
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
    printf("%s%d %s%d %sis thinking\n", CYAN, (int)timestamp_in_ms, RED, (*philo)->philo, RESET);
    // pthread_mutex_unlock(&(*philo)->info->think_lock);
	if (death_check(philo, timestamp_in_ms))
		return (1);
	return (0);
}

void *life(void *philo_num)
{
    long long timestamp_in_ms;
	t_philo *philo;
	philo = (t_philo *)philo_num;

	// long long time_bc = 0;
	// time_bc = time_now();
	
	timestamp_in_ms = 0;
	// printf("-> %lld\n", philo->info->time_bc);
	int loop = 0; //make this loop infinite
	while (loop < 5)
	{
		// printf("last meal before eating %d\n", philo->last_meal);
		if (eating(&philo, timestamp_in_ms))
			return (NULL);
		// printf("last meal after eating %d\n", philo->last_meal);
		 if (sleeping(&philo, timestamp_in_ms))
		 	return (NULL);
		 if (thinking(&philo, timestamp_in_ms))
		 	return (NULL);
		loop++;
	}
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

	// pthread_mutex_init(&info->think_lock, NULL);
	// pthread_mutex_init(&info->sleep_lock, NULL);
	pthread_mutex_init(&info->death_lock, NULL);
	i = 0;
	// long long time_bc = 0;
	info->time_bc = time_now();
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
	// pthread_mutex_destroy(&info->think_lock);
	// pthread_mutex_destroy(&info->sleep_lock);
	pthread_mutex_destroy(&info->death_lock);
	return (1);
}

int main(int ac, char **av)
{
    t_info info;
    
    if (!(parsing(ac, av, &info)))
        return (1);
    if (!(execution(&info))) // return 0 if false
        return (1);
    return (0);
}

// For tmrw

// eating meals death logic
// correct time printing


// fix printing time in the lab. Make sure it prints the correct time based on what the philo is doing. Check if the philo is doing the tasks at the expected/required time





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


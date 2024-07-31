/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:17 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/07/31 17:23:49 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philo *philo, double timestamp_in_ms)
{

    if (philo->philo == 1 || philo->philo == philo->info->philos)
    {
            if ((philo->philo == 1 && (philo->info->forks[0] != 1
            && philo->info->forks[philo->info->philos - 1] != 1))
            || (philo->philo == philo->info->philos 
	            && (philo->info->forks[0] != philo->info->philos
                && philo->info->forks[philo->info->philos - 1] != philo->info->philos)))
            {
				{
		            philo->info->forks[0] = philo ->philo;
		            philo->info->forks[philo->info->philos - 1] = philo ->philo;	/* code */
				}
            }
    }
	else
	{
	    philo->info->forks[philo->philo - 1] = philo ->philo;
	    philo->info->forks[philo->philo - 2] = philo ->philo;
	}
	int i = 0;
	i = 0;
    while (i < philo->info->philos)
	{
		printf("%d ", philo->info->forks[i]);
		i++;
	}
    printf("\n");
    
    // usleep(100);
    
    
    printf("%f %d has taken a fork\n", timestamp_in_ms, philo->philo); // modify the sleep to start from the last meal time (difference) & the begining of the program
    printf("%f %d has taken a fork\n", timestamp_in_ms, philo->philo);
    printf("%f %d is eating\n", timestamp_in_ms, philo->philo);
    usleep(10);// modify the time to be the required routine time
}

void sleeping(t_philo *philo, double timestamp_in_ms)
{
    printf("%f %d is sleeping\n", timestamp_in_ms, philo->philo);
    usleep(10);// modify the time to be the required routine time
}

void thinking(t_philo *philo, double timestamp_in_ms)
{
    printf("%f %d is thinking\n", timestamp_in_ms, philo->philo);
    usleep(10);// modify the time to be the required routine time
}
void *life(void *philo_num)
{
    struct timeval current_time;
    double timestamp_in_ms;
	t_philo *philo;
	philo = (t_philo *)philo_num;
	
    // int i = 0;
	// i = 0;
    // while (i < philo->info->philos)
	// {
	// 	printf("%d ", philo->info->forks[i]);
	// 	i++;
	// }
    // printf("\n");
    
    gettimeofday(&current_time, NULL);
    timestamp_in_ms = current_time.tv_sec * 1000 + (current_time.tv_usec) / 1000;
    eating(philo, timestamp_in_ms);
    sleeping(philo, timestamp_in_ms);
    thinking(philo, timestamp_in_ms);
    printf("%f %d died\n", timestamp_in_ms, philo->philo); //this should be monitord somehow to check for the death of any philo
    // if (philo)
        free(philo);
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
	int i;
    t_philo *philo;
	
	i = 0;
	while (i < info->philos)
	{
        philo = malloc(sizeof(t_philo));
        if (!philo)
            return (0);
        initializer(philo, info, i);
        // philo->total_meals = 0;
        // philo->last_meal = 0;
        // philo->philo = i + 1;
        // philo->info = info;
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

int main(int ac, char **av)
{
    t_info info;
    
    if (!(parsing(ac, av, &info)))
        return (1);   
    if (!(execution(&info)))
        return (1);
    return (0);
}

// Steps:
// 1. forks
// 2. mutex
// 3. routine
// 4. monitor

// 1. record the program starting time in a variable.

// 2. specify how would you find the time difference to check for the death of a philo & to specify the sleep time. Usleep is in micro sec and the program is in milli sec ***
// 3. specify the logic to follow e.g. even/odd OR monitor etc.
// 4. based on the logic speicify what variables we need to pass/modify/lock in a mutex. Create mutex accordingly.
// 5. check for leak & common cases
// 6. finalized the code
// 7. you can do the bonus if you finish early
// 8. Submit & Cerebrate 🥳🎉

// Execution:
// 1. Eat, think, sleep, (one action at a time)
// 2. two chopstick to be able to eat
// 3. The program stops when a philosopher dies of starvation.
// 4. Time in milliseconds
// 5. things to be printed
//         timestamp_in_ms X has taken a fork
//         timestamp_in_ms X is eating
//         timestamp_in_ms X is sleeping
//         timestamp_in_ms X is thinking
//         timestamp_in_ms X died
// 6. A displayed state message should not be mixed up with another message.
// 7. Your program must not have any data races.
// 8. no greedy philosopher
// 9. A message announcing a philosopher died should be displayed no more than 10 ms
// after the actual death of the philosopher.
// 10. the moment philosphers dies u must stop all threads and in the program
// 11. external function:
//         memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create,
//         pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,
//         pthread_mutex_unlock
// 12. Each philosopher should be a thread.
// 13. To prevent philosophers from duplicating forks, you should protect the forks state 
// with a mutex for each of them
// 14. As many forks as philosophers
// 15. all philosophers have eaten at least number_of_times_each_philosopher_must_eat
// times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
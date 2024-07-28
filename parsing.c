/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:11 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/07/29 00:35:26 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void info_init(int argc, char**av, t_info *info)
{
    info->forks = ft_atoi(av[1]);
    info->philos = ft_atoi(av[1]);
    info->t2die = ft_atoi(av[2]);
    info->t2eat = ft_atoi(av[3]);
    info->t2sleep = ft_atoi(av[4]);
    if (argc == 6)
        info->meals = ft_atoi(av[5]);
    else
        info->meals = -1;
}
int parsing(int ac, char **av, t_info *info)
{
    if (ac != 5 && ac != 6)
    {
        printf("wrong amount of arguements\n");
        return (0); 
    }
    else if (input_parsing(av))
    {
        info_init(ac, av, info);
        return (1);
    }
    else
    {
        printf("input invalid\n");
        return (0);
    }
}

// Parsing:
// 1. Minumum is one, 200 is maximum (number of philosopherss)
// 2. Your(s) program(s) should take the following arguments:
//         number_of_philosophers (number of forks)
//         time_to_die (how long they can survive without eating)
//         time_to_eat (time it takes for a philosopher to finish one meal)
//         time_to_sleep (The time a philosopher will spend sleeping)
//         [number_of_times_each_philosopher_must_eat] (optional)
//         (all philosophers have eaten at least number_of_times_each_philosopher_must_eat
//         times, the simulation stops. If not specified, the simulation stops when a philosopher dies.)

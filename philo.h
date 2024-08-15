/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:00:09 by thelmy            #+#    #+#             */
/*   Updated: 2024/08/12 19:00:09 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define RED "\033[31m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

typedef struct s_info
{
	int				philos;
	long long		time_bc;
	int				forks[200];
	pthread_mutex_t	fork_lock[200];
	int				t2die;
	int				t2eat;
	int				t2sleep;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	int				dead;
	int				meals;
}	t_info;

typedef struct s_philo
{
	t_info	*info;
	int		philo;
	int		last_meal;
	int		started_sleep;
	int		total_meals;
}	t_philo;

void		initializer(t_philo *philo, t_info *info, int i);

int			starting_threads(t_info *info,
				pthread_t threads[200], t_philo *philo);

int			execution(t_info *info);
long long	time_now(void);
int			one_philo(t_philo **philo, double timestamp_in_ms);
int			dead_philo(t_philo **philo, double timestamp_in_ms);
int			death_check(t_philo **philo, double timestamp_in_ms);

void		*life(void *philo_num);
int			specified_meals(t_philo *philo, long long timestamp_in_ms);
int			sleeping(t_philo **philo, double timestamp_in_ms);
int			thinking(t_philo **philo, double timestamp_in_ms);

int			ft_isnum(char *str);
int			ft_atoi(const char *str);
int			input_parsing(char **str);
int			parsing(int ac, char **av, t_info *info);
int			eating(t_philo **philo, double timestamp_in_ms);
#endif 

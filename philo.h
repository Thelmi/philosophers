
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_info
{
    int philos;
    int forks;
    int t2die;
    int t2eat;
    int t2sleep;
    int meals;
    // int program_starting_time; //this might be of "struct timeval" type instead. We also might do it differntly and record the time differently. I am just writing my current ideas.
} t_info;

typedef struct s_philo
{
    t_info  *info;
    int     philo;
    int     last_meal;
    int     total_meals;
} t_philo;

int ft_isnum(char *str);
int ft_atoi(const char *str);
int input_parsing(char **str);
int parsing(int ac, char **av, t_info *info);

#endif 

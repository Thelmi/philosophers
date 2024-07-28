
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

typedef struct s_info
{
    int philos;
    int forks;
    int t2die;
    int t2eat;
    int t2sleep;
    int meals;
} t_info;

int ft_isnum(char *str);
int ft_atoi(const char *str);
int input_parsing(char **str);
int parsing(int ac, char **av, t_info *info);

#endif 
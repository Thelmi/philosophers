
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>


#define RED "\033[31m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
    
typedef struct s_info
{
    int philos;
    long long time_bc;
    int forks[200];
    pthread_mutex_t fork_lock[200];
    int t2die;
    int t2eat;
    int t2sleep;
    //pthread_mutex_t sleep_lock;
    //pthread_mutex_t think_lock;
    pthread_mutex_t death_lock;
    pthread_mutex_t print_lock;
    int dead;
    
    int meals;
    // int program_starting_time; //this might be of "struct timeval" type instead. We also might do it differntly and record the time differently. I am just writing my current ideas.
} t_info;

typedef struct s_philo
{
    t_info  *info;
    int     philo;
    int     last_meal;
    int     started_sleep; //I added this to remove i from the meals time counter
    int     total_meals;
} t_philo;

int ft_isnum(char *str);
int ft_atoi(const char *str);
int input_parsing(char **str);
int parsing(int ac, char **av, t_info *info);

#endif 


#ifndef PHILO_H
# define PHILO_H

#include <string.h> //memset
#include <stdio.h> //printf
#include <stdlib.h> //malloc, free
#include <unistd.h> //write, usleep
#include <sys/time.h> //gettimeofday
#include <pthread.h> //pthread_create-detatch-join-mitex_init-mutex_destroy-mutex_lock-mutex_unlock
#include <limits.h> //INT_MAX - INT_MIN
#include <stdbool.h> //boolean

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef pthread_mutex_t t_mtx;

typedef struct s_fork{
    t_mtx       fork;
    long long   fork_id;

} t_fork;

typedef struct s_pos{ //not sure if needed??
    struct s_pos    *prev;
    struct s_pos    *next;
    long long       id;
    t_philo         *philo;

} t_pos;

typedef struct s_philo{
    long long   id;
    pthread_t   thread_id;
    long long   n_meals;
    bool        full;
    long long   last_meal_time; //determine death
    t_fork      *left_fork;
    t_fork      *right_fork;
    t_pos       *pos_philo;

} t_philo;

typedef struct s_symposium{ //store input args
    long long   n_philo;
    long long   time_to_die;
    long long   time_to_eat;
    long long   time_to_sleep;
    long long   n_need_to_eat; //keep in mind: optional arg
    long long   start_simulation;
    bool        end_simulation; //either dead or all philo full
    t_fork      *forks;
    t_philo     *philos;

} t_symposium;

int ft_error(const char *error_message);

#endif
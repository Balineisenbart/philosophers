

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_symposium t_symposium;

typedef struct s_forks{

    t_mtx           fork;
    unsigned int    fork_id;
} t_fork;

typedef struct s_philo{
    int         id;
    long long   meals_counter;
    bool        full;
    long long   last_meal_time; //he dead?
    t_fork      *right_fork;
    t_fork      *left_fork;
    pthread_t   thread_id; //needed to make philos threads
    t_symposium *symposium;

} t_philo;

typedef struct s_symposium{
    //input args
    long long n_philo;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep; //in ms
    long long n_meals;
    //needed for timestamp
    long long   start_symposium;
    bool        finish_symposium; //death or all full
    //general handling
    t_philo *philo;
    t_fork *fork;
} t_symposium;


#endif
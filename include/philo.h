

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_symposium t_symposium;

typedef struct s_forks{

    pthread_mutex_t fork;
    bool fork_mtx_init;
    unsigned int    fork_id;

} t_fork;

typedef struct s_philo{
    int         id;
    long long   meals_counter;
    bool        full;
    long long   last_meal_time;
    t_fork      *right_fork;
    t_fork      *left_fork;
    pthread_t   thread_id;
    pthread_t   monitor_id;
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
    //print locking
    pthread_mutex_t print_lock;
    //safety
    bool print_lock_init;
    bool philo_all;
    bool fork_all;

} t_symposium;

//utils
void error_exit(const char *error_message, t_symposium *symposium);
long long get_timestamp(void);
void print_status(const char *message, t_philo *philo);
void *monitor(void *arg);
void *monitor_finish(void *arg);

//mains
void parse_input(t_symposium *symposium, int argc, char **argv);
void init_symposium(t_symposium *symposium);
void start_symposium(t_symposium *symposium);
void        take_up_fork(t_philo *philo);
void        eating(t_philo *philo);
void        sleeping(t_philo *philo);
void        thinking(t_philo *philo);
void        death(t_philo *philo);
void clean_up(t_symposium *symposium);



#endif


#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_symposium t_symposium;

typedef struct s_forks{

    pthread_mutex_t fork;
    bool fork_mtx_init;
    unsigned int    fork_id;
    bool is_locked;

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
    pthread_mutex_t   meal_lock;
    pthread_mutex_t full_lock;
    bool meal_mtx_init;
    bool full_mtx_init;
    t_symposium *symposium;

    bool left_fork_locked;
    bool right_fork_locked;
    bool thread_init;

} t_philo;

typedef struct s_symposium{
    //input args
    long long n_philo;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    long long n_meals;
    //needed for timestamp
    long long   start_symposium;
    bool        finish_symposium;
    //general handling
    t_philo *philo;
    t_fork *fork;
    //print locking
    pthread_mutex_t print_lock;
    pthread_mutex_t finish_lock;
    pthread_mutex_t assembly_lock;
    pthread_mutex_t start_symposium_lock;
    pthread_mutex_t shutdown_lock;
    //safety
    bool print_lock_init;
    bool philo_all;
    bool fork_all;
    bool finish_mtx_init;
    bool flag;
    bool complete_assembly;
    bool assembly_lock_init;
    bool start_symposium_mtx_init;
    bool death_thread_flag;
    bool finish_thread_flag;
    bool shutdown_flag;
    bool shutdown_init;
    bool shutdown_thread_init;
    //monitoring
    pthread_t death_thread;
    pthread_t finish_thread;
    pthread_t shutdown_thread;

} t_symposium;

//utils
int error_exit(const char *error_message, t_symposium *symposium);
long long get_timestamp(t_symposium *symposium);
void print_status(const char *message, t_philo *philo);
void *monitor_death(void *arg);
void *monitor_full(void *arg);
void *monitor_shutdown(void *arg);

//mains
int         parse_input(t_symposium *symposium, int argc, char **argv);
int         init_symposium(t_symposium *symposium);
int         start_symposium(t_symposium *symposium);
void        take_up_fork(t_philo *philo);
void        eating(t_philo *philo);
void        sleeping(t_philo *philo);
void        thinking(t_philo *philo, bool pre_symposium);
bool        clean_up(t_symposium *symposium);
void        ft_usleep(long long duration, t_symposium *symposium);
void        assembly_complete(t_symposium *symposium);


#endif
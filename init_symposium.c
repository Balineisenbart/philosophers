
#include "philo.h"


static void init_forks(t_symposium *symposium)
{
    /*
    t_mtx           fork;
    unsigned int    fork_id;
    */
    long long i;

    i = 0;
    symposium->fork = malloc (symposium->n_philo * (sizeof(t_fork)));
    if (!symposium->fork)
        error_exit("Malloc for fork failed\n"); //possibly free everything else
    while ( i < symposium->n_philo)
    {
        symposium->fork[i].fork_id = i + 1;
        if (pthread_mutex_init(&symposium->fork[i].fork, NULL))
            error_exit("Mutex init fialed. Dig for error code for more info\n"); //possibly need to free stuff; mutex_destroy.. other structs??
        i++;
    }
}

static void init_philos(t_symposium *symposium)
{
    /*
    int         id;
    long long   meals_counter;
    bool        full;
    long long   last_meal_time; //he dead?

    t_fork      *right_fork;
    t_fork      *left_fork;
    pthread_t   thread_id; //needed to make philos threads
    t_symposium *symposium;
    */
    long long i;

    i = 0;
    symposium->philo = malloc (symposium->n_philo * (sizeof(t_philo)));
    if (!symposium->philo)
        error_exit("Malloc failed for philosophers\n"); //possibly free everything else
    while (symposium->n_philo > i)
    {   
        symposium->philo[i].id = i + 1;
        symposium->philo[i].meals_counter = 0;
        symposium->philo[i].full = false;
        symposium->philo[i].last_meal_time = 0;
        symposium->philo[i].left_fork = &symposium->fork[i]; //make sure to implement deadlock save.. odd ones pick right first
        symposium->philo[i].right_fork = &symposium->fork[(i + 1) % symposium->n_philo];
        pthread_create(&symposium->philo[i].thread_id, NULL, "some_function", "some arg for function");
        symposium->philo[i].symposium = symposium;
        i++;
    }
}

void init_symposium(t_symposium *symposium)
{
    /*
    X long long   start_symposium;
    X bool        finish_symposium; //death or all full
    //general handling
    t_philo *philo;
    t_fork *fork;
    */

    struct timeval tv;
    long long i;

    i = 0;
    gettimeofday(&tv, NULL);
    symposium->start_symposium = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    symposium->finish_symposium = false;

    init_forks(symposium);
    init_philos(symposium);
    while (i < symposium->n_philo)
    {
        if (pthread_join(&symposium->philo[i], NULL))
            error_exit("pthread_join fialed. Dig for error code for more info\n"); //possibly need to free stuff; mutex_destroy.. other structs??
        i++;
    }


   



}
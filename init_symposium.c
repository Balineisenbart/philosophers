
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

static void philo_routine(void *arg)
{
    /*• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.*/

    t_philo *philo = (t_philo *)arg;

    
    //-1 flag for no specified number of meals ??
    while (philo->full == false || 
        philo->last_meal_time < philo->symposium->time_to_die) //conditions is alive
    {
        take_up_fork(philo);// ->implement deadlock prevention
            //print_status("has taken a fork", philo);
        eating(philo);// ->need usleep time_to_eat
            //print_status("is eating", philo);
        sleeping(philo);// ->need usleep time_to_sleep
            //print_status("is sleeping", philo);
        thinking(philo);// ->only if not two forks available
            //print_status("is thinking", philo);
    }
    death(philo);
    return (NULL);
}

static void init_philos(t_symposium *symposium)
{
    /*
    int         id;
    long long   meals_counter;
    bool        full;
    long long   last_meal_time;
    t_fork      *right_fork;
    t_fork      *left_fork;
    pthread_t   thread_id;
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
        pthread_create(&symposium->philo[i].thread_id, NULL, philo_routine, &symposium->philo[i]);
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

    long long i;

    i = 0;
    symposium->start_symposium = get_timestamp();
    symposium->finish_symposium = false;
    if (pthread_mutex_init(&symposium->print_lock, NULL))
        error_exit("Mutex init failed for print lock\n");
    init_forks(symposium);
    init_philos(symposium);
    while (i < symposium->n_philo)
    {
        if (pthread_join(&symposium->philo[i].id, NULL))
            error_exit("pthread_join fialed. Dig for error code for more info\n"); //possibly need to free stuff; mutex_destroy.. other structs??
        i++;
    }
}

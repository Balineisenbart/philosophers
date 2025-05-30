
#include "philo.h"


static void init_forks(t_symposium *symposium)
{
    long long i;

    i = 0;
    symposium->fork = malloc (symposium->n_philo * (sizeof(t_fork)));
    if (!symposium->fork)
        error_exit("Malloc for fork failed\n", &symposium);
    symposium->fork_all = true;
    while ( i < symposium->n_philo)
    {
        symposium->fork[i].fork_id = i + 1;
        if (pthread_mutex_init(&symposium->fork[i].fork, NULL))
            error_exit("Mutex init fialed. Dig for error code for more info\n", &symposium);
        symposium->fork->fork_mtx_init = true;
        i++;
    }
}

static void init_philos(t_symposium *symposium)
{
    long long i;

    i = 0;
    symposium->philo = malloc (symposium->n_philo * (sizeof(t_philo)));
    if (!symposium->philo)
        error_exit("Malloc failed for philosophers\n", &symposium);
    symposium->philo_all = true;
    while (symposium->n_philo > i)
    {   
        symposium->philo[i].id = i + 1;
        symposium->philo[i].meals_counter = 0;
        symposium->philo[i].full = false;
        symposium->philo[i].last_meal_time = 0;
        symposium->philo[i].left_fork = &symposium->fork[i]; //make sure to implement deadlock save.. odd ones pick right first
        symposium->philo[i].right_fork = &symposium->fork[(i + 1) % symposium->n_philo];
        symposium->philo[i].symposium = symposium;
        i++;
    }
}

void init_symposium(t_symposium *symposium)
{
    long long i;

    i = 0;
    symposium->start_symposium = 0;
    symposium->finish_symposium = false;
    if (pthread_mutex_init(&symposium->print_lock, NULL))
        error_exit("Mutex init failed for print lock\n", &symposium);
    symposium->print_lock_init = true;
    init_forks(symposium);
    init_philos(symposium);
}

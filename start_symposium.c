
#include "philo.h"


void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    
    //-1 flag for no specified number of meals ??

    while (get_timestamp() < philo->symposium->start_symposium)
        usleep(50);
    death(philo); //might call monitor thread directly here. atm keep death() for readability
    while (!philo->symposium->finish_symposium) //conditions is alive
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
    return (NULL);
}

void start_symposium(t_symposium *symposium)
{
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    symposium->start_symposium = get_timestamp() + 100; //hardcoded 100ms - time to spawn all philos


    while (p < e)
        pthread_create(&p++->thread_id, NULL, philo_routine, p);
    t_philo *p = symposium->philo;
    while (p < e)
    {
        if (pthread_join(p++->id, NULL))
            error_exit("pthread_join fialed. Dig for error code for more info\n"); //possibly need to free stuff; mutex_destroy.. other structs??
    }
    
}
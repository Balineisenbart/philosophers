
#include "philo.h"


void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    bool finished;

    while (get_timestamp() < philo->symposium->start_symposium)
        usleep(50);

        
    death(philo); //might call monitor thread directly here. atm keep death() for readability
    
    while (1)
    {
        pthread_mutex_lock(&philo->symposium->finish_lock);
        finished = philo->symposium->finish_symposium;
        pthread_mutex_unlock(&philo->symposium->finish_lock);
        if (finished)
            break;
        take_up_fork(philo);
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return (NULL);
}

void start_symposium(t_symposium *symposium)
{
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    symposium->start_symposium = get_timestamp() + 100; //hardcoded 100ms - wa 10 * n_philo .. each philo has 10 ms time to spwan

    while (p < e)
    {
        pthread_create(&p->thread_id, NULL, philo_routine, p);
        p++;
    }
    if (symposium->n_meals != -1)
    {
        pthread_t finish_thread;
        pthread_create(&finish_thread, NULL, monitor_full, symposium);
        pthread_detach(finish_thread);
    }
    p = symposium->philo;
    while (p < e)
    {
        if (pthread_join(p->thread_id, NULL))
            error_exit("pthread_join fialed. Dig for error code for more info\n", symposium);
        p++;
    }
}
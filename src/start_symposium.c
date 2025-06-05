
#include "philo.h"


void *philo_routine(void *arg)  //-every action needs a check for finsh
{
    t_philo *philo = (t_philo *)arg;
    bool finished;

    while (get_timestamp() < philo->symposium->start_symposium)
        usleep(50);
    
    while (1)
    {
        pthread_mutex_lock(&philo->symposium->finish_lock);
        finished = philo->symposium->finish_symposium;
        pthread_mutex_unlock(&philo->symposium->finish_lock);
        if (finished)
            break;
        take_up_fork(philo);

        pthread_mutex_lock(&philo->symposium->finish_lock);
        finished = philo->symposium->finish_symposium;
        pthread_mutex_unlock(&philo->symposium->finish_lock);
        if (finished)
            break;
        eating(philo);

        pthread_mutex_lock(&philo->symposium->finish_lock);
        finished = philo->symposium->finish_symposium;
        pthread_mutex_unlock(&philo->symposium->finish_lock);
        if (finished)
            break;
        sleeping(philo);

        pthread_mutex_lock(&philo->symposium->finish_lock);
        finished = philo->symposium->finish_symposium;
        pthread_mutex_unlock(&philo->symposium->finish_lock);
        if (finished)
            break;
        thinking(philo);

    }
    return (NULL);
}


void start_symposium(t_symposium *symposium)
{
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    symposium->start_symposium = get_timestamp() + (50 * symposium->n_philo);

    while (p < e)
    {
        pthread_create(&p->thread_id, NULL, philo_routine, p);
        pthread_create(&p->monitor_id, NULL, monitor_death, p); //keep here outside of routine??
        pthread_detach(p->monitor_id);
        p++;
    }
    if (symposium->n_meals != -1)
    {
        pthread_t finish_thread;
        pthread_create(&finish_thread, NULL, monitor_full, symposium);
        pthread_detach(finish_thread);
    }
    p = symposium->philo;
    while (p < e) //maybe do in cleanup?? -- ulimit -v <smaller memory>
    {
        if (pthread_join(p->thread_id, NULL))
            error_exit("pthread_join fialed. Dig for error code for more info\n", symposium);
        p++;
    }
}


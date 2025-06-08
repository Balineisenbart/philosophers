
#include "philo.h"


void *philo_routine(void *arg)  //better handling of finish check
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
    if (philo->left_fork_locked)
    {
        pthread_mutex_unlock(&philo->left_fork->fork);
        philo->left_fork_locked = false;
    }
    if (philo->right_fork_locked)
    {
        pthread_mutex_unlock(&philo->right_fork->fork);
        philo->right_fork_locked = false;
    }
    return (NULL);
}


int start_symposium(t_symposium *symposium)
{
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    symposium->start_symposium = get_timestamp() + (50 * symposium->n_philo);

    while (p < e)
    {
        if (pthread_create(&p->thread_id, NULL, philo_routine, p))
            return (error_exit("failed to create thread_id\n", symposium));
        p++;
    }
    if (pthread_create(&symposium->death_thread, NULL, monitor_death, symposium))
        return (error_exit("failed to create death_thread\n", symposium));

    if (symposium->n_meals != -1)
    {
        if (pthread_create(&symposium->finish_thread, NULL, monitor_full, symposium))
            return (error_exit("failed to create finish/isfull_thread\n", symposium));
    }
    return (0);
}


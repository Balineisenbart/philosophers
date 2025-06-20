
#include "philo.h"

void assembly_complete(t_symposium *symposium)
{
    while (1)
    {
        pthread_mutex_lock(&symposium->assembly_lock);
        if (symposium->complete_assembly == true)
        {
            pthread_mutex_unlock(&symposium->assembly_lock);
            break;
        }
        pthread_mutex_unlock(&symposium->assembly_lock);   
        ft_usleep(10, symposium);
    }
}

static void desync(t_philo *philo)
{
    if (philo->symposium->n_philo % 2 == 0)
    {
        if (philo->id % 2 == 0)
            ft_usleep(30000, philo->symposium);
    }
    else
    {
        if (philo->id % 2)
            thinking(philo, false);
    }

}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    bool finished;

    assembly_complete(philo->symposium);
    desync(philo);
    
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
        thinking(philo, true);

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


    while (p < e)
    {
        if (pthread_create(&p->thread_id, NULL, philo_routine, p))
            return (error_exit("failed to create thread_id\n", symposium));
        p->thread_init = true;
        p++;
    }


    if (pthread_create(&symposium->death_thread, NULL, monitor_death, symposium))
        return (error_exit("failed to create death_thread\n", symposium));
    symposium->death_thread_flag = true;

    if (symposium->n_meals != -1)
    {
        if (pthread_create(&symposium->finish_thread, NULL, monitor_full, symposium))
            return (error_exit("failed to create finish/isfull_thread\n", symposium));
        symposium->finish_thread_flag = true;
    }

    symposium->start_symposium = get_timestamp();

    pthread_mutex_lock(&symposium->assembly_lock);
    symposium->complete_assembly = true;
    pthread_mutex_unlock(&symposium->assembly_lock);

    return (0);
}


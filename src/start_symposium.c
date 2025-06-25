
#include "philo.h"

static bool check_finish(t_philo *philo, bool finished)
{
    pthread_mutex_lock(&philo->symposium->finish_lock);
    finished = philo->symposium->finish_symposium;
    pthread_mutex_unlock(&philo->symposium->finish_lock);
    return (finished);
}

static void do_routine(t_philo *philo)
{
    bool finished;

    finished = false;
    while (1)
    {
        if (check_finish(philo, finished))
            break;
        take_up_fork(philo);
        if (check_finish(philo, finished))
            break;
        eating(philo);
        if (check_finish(philo, finished))
            break;
        sleeping(philo);
        if (check_finish(philo, finished))
            break;
        thinking(philo, true);
    }
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    assembly_complete(philo->symposium);
    desync(philo);
    do_routine(philo);
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


static void create_thread(t_symposium *symposium)
{
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;

    if (pthread_create(&symposium->shutdown_thread, NULL, monitor_shutdown, symposium))
        return (error_exit("failed to crate shutdown_thread\n", symposium));
    symposium->shutdown_thread_init = true;
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
    return (0);
}

int start_symposium(t_symposium *symposium)
{
    if (create_thread(symposium))
        return (-1);
    symposium->start_symposium = get_timestamp(symposium);
    pthread_mutex_lock(&symposium->assembly_lock);
    symposium->complete_assembly = true;
    pthread_mutex_unlock(&symposium->assembly_lock);

    return (0);
}
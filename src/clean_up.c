

#include "philo.h"

bool clean_up(t_symposium *symposium)
{
    t_fork *f = symposium->fork;
    t_fork *e_f = f + symposium->n_philo;
    t_philo *p = symposium->philo;
    t_philo *e_p = p + symposium->n_philo;
    bool error_status;

    error_status = false;

    if (symposium->shutdown_thread_init)
    {
        if (pthread_join(symposium->shutdown_thread, NULL))
        {
            printf("pthread join failed for shut down thread\n");
            error_status = true;
        }
    }
    if (symposium->death_thread_flag)
        {
        if (pthread_join(symposium->death_thread, NULL))
        {
            printf("pthread_join death_thread fialed. Dig for error code for more info\n");
            error_status = true;
        }
    }
    if (symposium->n_meals != -1)
    {
        if (symposium->finish_thread_flag)
        {
            if (pthread_join(symposium->finish_thread, NULL))
            {
                printf("pthread_join finish_thread fialed. Dig for error code for more info\n");
                error_status = true;
            }
        }
    }
    while (p < e_p)
    {
        if (p->thread_init)
        {
            if (pthread_join(p->thread_id, NULL))
            {
                printf("pthread_join thread_id fialed. Dig for error code for more info\n");
                error_status = true;
            }
        }
        else
            break;
        p++;
    }
    p = symposium->philo;
    if (symposium->philo_all)
    {
         while (p < e_p)
        {
            if (p->meal_mtx_init)
            {
                if (pthread_mutex_destroy(&p->meal_lock))
                {
                    printf ("Mutex destroy failed on meal_lock\n");
                    error_status = true;
                }
            }
            if (p->full_mtx_init)
            {
                if(pthread_mutex_destroy(&p->full_lock))
                {
                    printf ("Mutex destroy failed on full_lock\n");
                    error_status = true;
                }
            }
            p++;
        }
        free(symposium->philo);
        symposium->philo = NULL;
    }
    if (symposium->fork_all)
    {
        while (f < e_f)
        {
            if (f->fork_mtx_init)
            {                    
                if (pthread_mutex_destroy(&f->fork))
                {
                    printf ("Mutex destroy failed on fork :: in clean_up\n");
                    error_status = true;
                }
            }
            f++;
        }
        free(symposium->fork);
        symposium->fork = NULL;
    }
    if (symposium->print_lock_init)
    {
        if (pthread_mutex_destroy(&symposium->print_lock))
        {
            printf ("Mutex destroy failed on print_lock\n");
            error_status = true;
        }
    }
    if (symposium->finish_mtx_init)
    {
        if (pthread_mutex_destroy(&symposium->finish_lock))
        {
            printf ("Mutex destroy failed on finish_lock\n");
            error_status = true;
        }
    }
    if (symposium->assembly_lock_init)
    {
        if (pthread_mutex_destroy(&symposium->assembly_lock))
        {
            printf ("Mutex destroy failed on assembly lock\n");
            error_status = true;
        }
    }

    return (error_status);
}

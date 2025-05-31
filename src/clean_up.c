

#include "philo.h"

//need to modularize .> clean mutex fork & print_lock separately
//wa print_lock locked?? -> separate check??

void clean_up(t_symposium *symposium)
{
    t_fork *p_f = symposium->fork;
    t_fork *e = p_f + symposium->n_philo;
    t_philo *p_p = symposium->philo;
    t_philo *e_p = p_p + symposium->n_philo;

    if (symposium->philo_all)
    {
         while (p_p < e_p)
        {
            if (p_p->meal_mtx_init)
            {
                if (pthread_mutex_destroy(&p_p->meal_lock))
                {
                    printf ("Mutex destroy failed on meal_lock\n");
                    exit(EXIT_FAILURE);
                }
            }
            if (p_p->full_mtx_init)
            {
                if(pthread_mutex_destroy(&p_p->full_lock))
            {
                    printf ("Mutex destroy failed on full_lock\n");
                    exit(EXIT_FAILURE);
            }
            }
            p_p++;
        }
        free(symposium->philo);
        symposium->philo = NULL;
    }
    if (symposium->fork_all)
    {
        while (p_f < e)
        {
            if (p_f->fork_mtx_init)
            {
                if (pthread_mutex_destroy(&p_f->fork))
                {
                    printf ("Mutex destroy failed on fork\n");
                    exit(EXIT_FAILURE);
                }
            }
            p_f++;
        }
        free(symposium->fork);
        symposium->fork = NULL;
    }
    if (symposium->print_lock_init)
    {
        if (pthread_mutex_destroy(&symposium->print_lock))
        {
            printf ("Mutex destroy failed on print_lock\n");
            exit(EXIT_FAILURE);
        }
    }
    if (symposium->finish_mtx_init)
    {
        if (pthread_mutex_destroy(&symposium->finish_lock))
        {
            printf ("Mutex destroy failed on finish_lock\n");
            exit(EXIT_FAILURE);
        }
    }
}



#include "philo.h"

//need to modularize .> clean mutex fork & print_lock separately
//wa print_lock locked?? -> separate check??
void clean_up(t_symposium *symposium)
{
    t_fork *p = symposium->fork;
    t_fork *e = p + symposium->n_philo; 
    if (symposium->philo_all)
    {
        free(symposium->philo);
        symposium->philo = NULL;
    }
    if (symposium->fork_all)
    {
        while (p < e)
        {
            if (p->fork_mtx_init)
            {
                if (pthread_mutex_destroy(&p->fork))
                {
                    printf ("Mutex destroy failed on fork\n");
                    exit(EXIT_FAILURE);
                }
            }
            p++;
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
}



#include "philo.h"

//need to modularize .> clean mutex fork & print_lock separately
//wa print_lock locked?? -> separate check??


/*
    //general handling
    t_philo *philo;                                  ->free
            pthread_t   thread_id;        ->detatch
            pthread_t   monitor_id;       ->detatch
            pthread_mutex_t   meal_lock;  ->destroy
            pthread_mutex_t full_lock;    ->destroy
            bool meal_mtx_init;
            bool full_mtx_init;

    t_fork *fork;                            ->free
            pthread_mutex_t fork; ->destroy
            bool fork_mtx_init;

    //print locking
    pthread_mutex_t print_lock;  ->destroy
    pthread_mutex_t finish_lock; ->destroy

    //safety
    bool print_lock_init;
    bool philo_all;
    bool fork_all;
    bool finish_mtx_init;
*/

void clean_up(t_symposium *symposium)
{
    t_fork *f = symposium->fork;
    t_fork *e_f = f + symposium->n_philo;
    t_philo *p = symposium->philo;
    t_philo *e_p = p + symposium->n_philo;

    if (symposium->philo_all)
    {
         while (p < e_p)
        {
            if (p->meal_mtx_init)
            {
                if (pthread_mutex_destroy(&p->meal_lock))
                {
                    printf ("Mutex destroy failed on meal_lock\n");
                    exit(EXIT_FAILURE);
                }
            }
            if (p->full_mtx_init)
            {
                if(pthread_mutex_destroy(&p->full_lock))
            {
                    printf ("Mutex destroy failed on full_lock\n");
                    exit(EXIT_FAILURE);
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
                    printf ("Mutex destroy failed on fork\n");
                    exit(EXIT_FAILURE);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:14:06 by astoiber          #+#    #+#             */
/*   Updated: 2025/06/25 17:14:07 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

bool clean_up_monitor(t_symposium *symposium, bool error_status)
{
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
    }return (error_status);
}

bool clean_up_join(t_symposium *symposium, bool error_status)
{
    t_philo *p = symposium->philo;
    t_philo *e_p = p + symposium->n_philo;

    if (symposium->n_meals != -1)
    {
        if (symposium->finish_thread_flag)
            error_status = safe_join(symposium->finish_thread, error_status, "pthread_join finish_thread fialed. Dig for error code for more info");
    }
    while (p < e_p)
    {
        if (p->thread_init)
            error_status = safe_join(p->thread_id, error_status, "pthread_join thread_id fialed. Dig for error code for more info");
        else
            break;
        p++;
    }
    return (error_status);
}

bool clean_up_philos(t_symposium *symposium, bool error_status)
{
    t_philo *p = symposium->philo;
    t_philo *e_p = p + symposium->n_philo;

    if (symposium->philo_all)
    {
        while (p < e_p)
        {
            if (p->meal_mtx_init)
                error_status = safe_mtx_destroy_philo(symposium->philo->meal_lock, error_status, "Mutex destroy failed on meal_lock");
            if (p->full_mtx_init)
                error_status = safe_mtx_destroy_philo(symposium->philo->full_lock, error_status, "Mutex destroy failed on full_lock");
            p++;
        }
        free(symposium->philo);
        symposium->philo = NULL;
    }
    return (error_status);
}

bool clean_up_fork(t_symposium *symposium, bool error_status)
{
    t_fork *f = symposium->fork;
    t_fork *e_f = f + symposium->n_philo;

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
    return (error_status);
}

bool clean_up_destroy(t_symposium *symposium, bool error_status)
{
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

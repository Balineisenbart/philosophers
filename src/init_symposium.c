/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_symposium.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:14:18 by astoiber          #+#    #+#             */
/*   Updated: 2025/06/25 17:20:04 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int init_forks(t_symposium *symposium)
{
    long long i;

    i = 0;
    symposium->fork = malloc (symposium->n_philo * (sizeof(t_fork)));
    if (!symposium->fork)
        return(error_exit("Malloc for fork failed\n", symposium));
    memset(symposium->fork, 0, symposium->n_philo * sizeof(t_fork));
    symposium->fork_all = true;
    while (i < symposium->n_philo)
    {
        symposium->fork[i].fork_id = i + 1;
        if (pthread_mutex_init(&symposium->fork[i].fork, NULL))
            return(error_exit("Mutex init fialed. Dig for error code for more info\n", symposium));
        symposium->fork[i].fork_mtx_init = true;
        i++;
    }
    return (0);
}

static int loop_philo_init(t_symposium *symposium)
{
    long long i;

    i = 0;
    while (symposium->n_philo > i)
    {   
        symposium->philo[i].id = i + 1;
        symposium->philo[i].meals_counter = 0;
        symposium->philo[i].full = false;
        if (pthread_mutex_init(&symposium->philo[i].full_lock, NULL))
            return(error_exit("Mutex init failed on full lock\n", symposium));
        symposium->philo[i].full_mtx_init = true;
        symposium->philo[i].last_meal_time = 0;
        symposium->philo[i].left_fork = &symposium->fork[i];
        symposium->philo[i].right_fork = &symposium->fork[(i + 1) % symposium->n_philo];
        symposium->philo[i].symposium = symposium;
        if (pthread_mutex_init(&symposium->philo[i].meal_lock, NULL))
                return(error_exit("Mutex init failed for meal lock\n", symposium));
        symposium->philo[i].meal_mtx_init = true,
        symposium->philo[i].thread_init = false;
        i++;
    }
    return (0);
}

static int init_philos(t_symposium *symposium)
{
    symposium->philo = malloc (symposium->n_philo * (sizeof(t_philo)));
    if (!symposium->philo)
        return(error_exit("Malloc failed for philosophers\n", symposium));
    memset(symposium->philo, 0, symposium->n_philo * sizeof(t_philo));
    symposium->philo_all = true;
    if (loop_philo_init(symposium))
        return (-1);
    return (0);
}

static int init_mtx(t_symposium *symposium)
{
    if (pthread_mutex_init(&symposium->print_lock, NULL))
        return(error_exit("Mutex init failed for print lock\n", symposium));
    symposium->print_lock_init = true;

    if (pthread_mutex_init(&symposium->finish_lock, NULL))
        return(error_exit("Mutex init failed for finish lock\n", symposium));
    symposium->finish_mtx_init = true;

    if (pthread_mutex_init(&symposium->assembly_lock, NULL))
        return(error_exit("Mutex init failed for assembly lock\n", symposium));
    symposium->assembly_lock_init = true;

    if (pthread_mutex_init(&symposium->start_symposium_lock, NULL))
        return (error_exit("Mutex init failed on start symposium\n", symposium));
    symposium->start_symposium_mtx_init = true;

    if (pthread_mutex_init(&symposium->shutdown_lock, NULL))
        return(error_exit("Mutex init failed on shutdown lock\n", symposium));
    symposium->shutdown_init = true;
    return (0);
}

int init_symposium(t_symposium *symposium)
{
    symposium->start_symposium = 0;
    symposium->finish_symposium = false;
    symposium->complete_assembly = false;
    symposium->death_thread_flag = false;
    symposium->finish_thread_flag = false;
    symposium->shutdown_flag = false;
    symposium->shutdown_thread_init = false;
    if (init_mtx(symposium))
        return (-1);
    if (init_forks(symposium))
        return (1);
    if (init_philos(symposium))
        return (1);
    return (0);
}

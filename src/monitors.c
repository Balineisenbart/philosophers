/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:14:30 by astoiber          #+#    #+#             */
/*   Updated: 2025/06/25 17:21:22 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_death(t_philo *cur, t_symposium *symposium)
{
    long long last_meal;
    long long now;

    pthread_mutex_lock(&cur->meal_lock);
    last_meal = cur->last_meal_time;
    now = get_timestamp(symposium);
    if ((last_meal == 0 && ((now - cur->symposium->start_symposium) > cur->symposium->time_to_die)) \
    || (last_meal != 0 && (((now - cur->symposium->start_symposium) - last_meal) > cur->symposium->time_to_die)))
    {
        print_status("died", cur);
        pthread_mutex_lock(&cur->symposium->finish_lock);
        cur->symposium->finish_symposium = true;
        pthread_mutex_unlock(&cur->symposium->finish_lock);
        pthread_mutex_unlock(&cur->meal_lock);
        pthread_mutex_lock(&symposium->shutdown_lock);
        symposium->shutdown_flag = true;
        pthread_mutex_unlock(&symposium->shutdown_lock);
        return (1);
    }
    pthread_mutex_unlock(&cur->meal_lock);
    return (0);
}

void *monitor_death(void *arg)
{
    t_symposium *symposium = (t_symposium *)arg;
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    t_philo *cur;

    assembly_complete(symposium);
    while(1)
    {
        if (check_finish(symposium))
            break;
        cur = p;
        while (cur < e)
        {
            if (check_death(cur++, symposium))
                return (NULL);
        }
        ft_usleep(100, symposium);
    }
    return (NULL);
}

static int check_all_full(t_philo *cur, t_philo *e, t_symposium *symposium, bool all_full)
{
    while (cur < e)
    {
        pthread_mutex_lock(&cur->full_lock);
        if (!cur->full)
            all_full = false;
        pthread_mutex_unlock(&cur->full_lock);
        if (!all_full)  
            return (0);
        cur++;
    }
    if (all_full) 
    {
        pthread_mutex_lock(&symposium->finish_lock);
        symposium->finish_symposium = true;
        pthread_mutex_unlock(&symposium->finish_lock);
        pthread_mutex_lock(&symposium->shutdown_lock);
        symposium->shutdown_flag = true;
        pthread_mutex_unlock(&symposium->shutdown_lock);
        return (1);
    }
    return (0);
}

void *monitor_full(void *arg)
{

    t_symposium *symposium = (t_symposium *)arg;
    bool all_full;
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    t_philo *cur;

    assembly_complete(symposium);
    while (1)
    {
        if (check_finish(symposium))
            break;
        all_full = true;
        cur = p;
        if (check_all_full(cur, e, symposium, all_full))
            return (NULL);
        ft_usleep(100, symposium);
    }
    return (NULL);
}

void *monitor_shutdown(void *arg)
{
    t_symposium *symposium = (t_symposium *)arg;

    while (1)
    {
        pthread_mutex_lock(&symposium->shutdown_lock);
        pthread_mutex_lock(&symposium->finish_lock);
        if (symposium->shutdown_flag)
        {
            symposium->finish_symposium = true;
            pthread_mutex_unlock(&symposium->finish_lock);
            pthread_mutex_unlock(&symposium->shutdown_lock);
            break;
        }
        pthread_mutex_unlock(&symposium->finish_lock);
        pthread_mutex_unlock(&symposium->shutdown_lock);
        ft_usleep(100, symposium);
    }
    return (NULL);
}

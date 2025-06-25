/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:15:10 by astoiber          #+#    #+#             */
/*   Updated: 2025/06/25 17:15:20 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void ft_usleep(long long duration, t_symposium *symposium)
{
    long long start;
    long long now;

    start = get_timestamp(symposium) * 1000;
    now = start;
    while ((now - start) < duration)
    {
        pthread_mutex_lock(&symposium->finish_lock);
        if (symposium->finish_symposium)
        {
            pthread_mutex_unlock(&symposium->finish_lock);
            break;
        }
        pthread_mutex_unlock(&symposium->finish_lock);

        usleep(250);
        now = get_timestamp(symposium) * 1000;
    }
}

int error_exit(const char *error_message, t_symposium *symposium)
{
    printf("%s\n", error_message);
    printf("Valid Input Arguments: \n");
    printf("number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
    pthread_mutex_lock(&symposium->finish_lock);
    symposium->finish_symposium = true;
    pthread_mutex_unlock(&symposium->finish_lock);
    pthread_mutex_lock(&symposium->assembly_lock);
    symposium->complete_assembly = true;
    pthread_mutex_unlock(&symposium->assembly_lock);
    if (symposium->flag)
        clean_up(symposium);
    return (-1);    
}

long long get_timestamp(t_symposium *symposium)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
    {
        pthread_mutex_lock(&symposium->shutdown_lock);
        symposium->shutdown_flag = true;
        pthread_mutex_unlock(&symposium->shutdown_lock);
    }

    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

void print_status(const char *message, t_philo *philo)
{
    long long symposium_time;
    long long now;

    now = get_timestamp(philo->symposium);

    symposium_time = now - philo->symposium->start_symposium;

    pthread_mutex_lock(&philo->symposium->finish_lock);
    if (!philo->symposium->finish_symposium)
        printf("%lld %d %s\n", symposium_time, philo->id, message);
    pthread_mutex_unlock(&philo->symposium->finish_lock);
}

void *error_message(char *message)
{
    printf("%s\n", message);
    return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:14:11 by astoiber          #+#    #+#             */
/*   Updated: 2025/06/25 17:14:12 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

bool safe_mtx_destroy_philo(pthread_mutex_t mtx, bool error_status, char *message)
{
    if (pthread_mutex_destroy(&mtx))
    {
        printf ("%s\n", message);
        error_status = true;
    }
    return (error_status);
}

bool safe_join(pthread_t thread, bool error_status, char *message)
{
    if (pthread_join(thread, NULL))
    {
        printf ("%s\n", message);
        error_status = true;
    }
    return (error_status);
}

bool clean_up(t_symposium *symposium)
{
    bool error_status;

    error_status = false;
    if (!clean_up_monitor(symposium, error_status))
        error_status = true;
    if (!clean_up_join(symposium, error_status))
        error_status = true;
    if (!clean_up_philos(symposium, error_status))
        error_status = true;
    if (!clean_up_fork(symposium, error_status))
        error_status = true;
    if (!clean_up_destroy(symposium, error_status))
        error_status = true;
    return (error_status);
}

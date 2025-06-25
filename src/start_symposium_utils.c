/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_symposium_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:14:46 by astoiber          #+#    #+#             */
/*   Updated: 2025/06/25 17:14:47 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"


void desync(t_philo *philo)
{
    if (philo->symposium->n_philo % 2 == 0)
    {
        if (philo->id % 2 == 0)
            ft_usleep(30000, philo->symposium);
    }
    else
    {
        if (philo->id % 2)
            thinking(philo, false);
    }
}

void assembly_complete(t_symposium *symposium)
{
    while (1)
    {
        pthread_mutex_lock(&symposium->assembly_lock);
        if (symposium->complete_assembly == true)
        {
            pthread_mutex_unlock(&symposium->assembly_lock);
            break;
        }
        pthread_mutex_unlock(&symposium->assembly_lock);   
        ft_usleep(10, symposium);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:14:24 by astoiber          #+#    #+#             */
/*   Updated: 2025/06/25 17:21:25 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_symposium symposium;

    symposium.flag = false;
    if (argc < 5 || argc > 6)
        return (error_exit("Number of Input invalid\n", &symposium));
    else
    {
        symposium.flag = true;
        if (parse_input(&symposium, argc, argv) == -1)
            return (1);
        if (init_symposium(&symposium) == -1)
            return (1);
        if (start_symposium(&symposium) == -1)
            return (1);
        if (clean_up(&symposium))
            return (1);
    }
    return (0);
}

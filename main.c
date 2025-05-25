#include "philo.h"




int main(int argc, char **argv)
{
    t_symposium symposium;

    if (argc < 5 || argc > 6)
        ft_error("Use: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
    parse_symposium(&symposium, argc, **argv);
    init_symposium(&symposium);
    start_symposium(&symposium);
    clean_symposium(&symposium); //->when all philos full or philo dead
    return 0;
}
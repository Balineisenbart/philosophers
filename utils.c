
#include "philo.h"


void error_exit(const char *error_message)
{
    printf("%s\n", error_message);
    printf("Valid Input Arguments: \n")
    printf("number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
    exit(EXIT_FAILURE);
}
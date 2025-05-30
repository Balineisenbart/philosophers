
#include "philo.h"


void error_exit(const char *error_message, t_symposium *symposium)
{
    printf("%s\n", error_message);
    printf("Valid Input Arguments: \n");
    printf("number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
    clean_up(symposium);
    exit(EXIT_FAILURE);
}

long long get_timestamp(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_status(const char *message, t_philo *philo)
{
    pthread_mutex_lock(&philo->symposium->print_lock);
    if (!philo->symposium->finish_symposium)
        printf("%lld %d %s\n", get_timestamp() - philo->symposium->start_symposium, philo->id, message);
    pthread_mutex_unlock(&philo->symposium->print_lock);
}

void *monitor(void *arg)
{
    //function to monitor if a philo is still alive 
    //if dead, immediately print death and free everything -> simulation stops
    t_philo *philo = (t_philo *)arg;

    while(!philo->symposium->finish_symposium)
    {
        if ((philo->last_meal_time == 0 && (get_timestamp() - philo->symposium->start_symposium) > philo->symposium->time_to_die) \
        || (philo->last_meal_time != 0 && (get_timestamp() - philo->last_meal_time > philo->symposium->time_to_die))) 
        {
            print_status("died", philo);
            philo->symposium->finish_symposium = true;
            break;
        }
        usleep(1000);
    }
    return (NULL);
}

void *monitor_finish(void *arg)
{

    t_symposium *symposium = (t_symposium *)arg;

    bool all_full;
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;

    all_full = true;
    while (p < e)
    {
        if (!p->full)
        {
            all_full = false;
            break;
        }
        p++;
    }
    if (all_full)
        symposium->finish_symposium = true; 
    return (NULL);      
}

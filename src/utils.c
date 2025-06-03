
#include "philo.h"


void error_exit(const char *error_message, t_symposium *symposium)
{
    printf("%s\n", error_message);
    printf("Valid Input Arguments: \n");
    printf("number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
    if (symposium->flag)
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
    pthread_mutex_lock(&philo->symposium->finish_lock);
    if (!philo->symposium->finish_symposium)
        printf("%lld %d %s\n", get_timestamp() - philo->symposium->start_symposium, philo->id, message);
    pthread_mutex_unlock(&philo->symposium->finish_lock);
}

void *monitor_death(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long long last_meal;
    
    while(1)
    {
        pthread_mutex_lock(&philo->symposium->finish_lock);
        if (philo->symposium->finish_symposium)
        {
            pthread_mutex_unlock(&philo->symposium->finish_lock);
            break;
        }
        pthread_mutex_unlock(&philo->symposium->finish_lock);
        
        pthread_mutex_lock(&philo->meal_lock);
        last_meal = philo->last_meal_time;
        pthread_mutex_unlock(&philo->meal_lock);
        
        if ((last_meal == 0 && ((get_timestamp() - philo->symposium->start_symposium) > philo->symposium->time_to_die)) \
        || (last_meal != 0 && (((get_timestamp() - philo->symposium->start_symposium) - last_meal) > philo->symposium->time_to_die))) 
        {
            print_status("died", philo);
            pthread_mutex_lock(&philo->symposium->finish_lock);
            philo->symposium->finish_symposium = true;
            pthread_mutex_unlock(&philo->symposium->finish_lock);
            break;
        }
        usleep(1000);
    }
    return (NULL);
}

void *monitor_full(void *arg)
{

    t_symposium *symposium = (t_symposium *)arg;

    bool all_full;
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    t_philo *cur;

    while (1)
    {
        pthread_mutex_lock(&symposium->finish_lock);
        if (symposium->finish_symposium)
        {
            pthread_mutex_unlock(&symposium->finish_lock);
            break;
        }
        pthread_mutex_unlock(&symposium->finish_lock);
        all_full = true;
        cur = p;
        while (cur < e)
        {
            pthread_mutex_lock(&cur->full_lock);
            if (!cur->full)
                all_full = false;
            pthread_mutex_unlock(&cur->full_lock);
            if (!all_full)  
                break;
            cur++;
        }
        if (all_full) 
        {
            pthread_mutex_lock(&symposium->finish_lock);
            symposium->finish_symposium = true;
            pthread_mutex_unlock(&symposium->finish_lock);
            break;
        }
    }
    return (NULL);      
}


#include "philo.h"

int ft_usleep(long long duration, t_symposium *symposium, long long)
{
    long long start;
    long long now;

    start = get_timestamp(symposium);
    if (start == -1)
        return (-1);
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
        now = get_timestamp(symposium);
        if (now == -1)
            return (-1);
    }
}

int error_exit(const char *error_message, t_symposium *symposium)
{
    printf("%s\n", error_message);
    printf("Valid Input Arguments: \n");
    printf("number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \n");
    if (symposium->flag)
        clean_up(symposium);
    return (-1);    
}

long long get_timestamp(t_symposium *symposium)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return (error_exit("get_timeofday failed\n", symposium));
    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void print_status(const char *message, t_philo *philo, long long time)
{
    long long symposium_time;
    /*long long now;

    now = get_timestamp(philo->symposium);*/

    symposium_time = time - philo->symposium->start_symposium;
    pthread_mutex_lock(&philo->symposium->finish_lock);
    if (!philo->symposium->finish_symposium)
        printf("%lld %d %s\n", symposium_time, philo->id, message);
    pthread_mutex_unlock(&philo->symposium->finish_lock);
}


void *monitor_death(void *arg)
{
    t_symposium *symposium = (t_symposium *)arg;
    t_philo *p = symposium->philo;
    t_philo *e = p + symposium->n_philo;
    t_philo *cur;
    long long last_meal;
    long long now;

    while(1)
    {
        pthread_mutex_lock(&symposium->finish_lock);
        if (symposium->finish_symposium)
        {
            pthread_mutex_unlock(&symposium->finish_lock);
            break;
        }
        pthread_mutex_unlock(&symposium->finish_lock);
        
        cur = p;
        while (cur < e)
        {
            pthread_mutex_lock(&cur->meal_lock);
            last_meal = cur->last_meal_time;
            now = get_timestamp(symposium);
            if (now == -1)
                return (NULL);

            if ((last_meal == 0 && ((now - cur->symposium->start_symposium) > cur->symposium->time_to_die)) \
            || (last_meal != 0 && (((now - cur->symposium->start_symposium) - last_meal) > cur->symposium->time_to_die)))
            {
                print_status("died", cur);
                pthread_mutex_lock(&cur->symposium->finish_lock);
                cur->symposium->finish_symposium = true;
                pthread_mutex_unlock(&cur->symposium->finish_lock);
                pthread_mutex_unlock(&cur->meal_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&cur->meal_lock);
            cur++;
        }
        ft_usleep(100, symposium);
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
        ft_usleep(100, symposium);
    }
    return (NULL);      
}

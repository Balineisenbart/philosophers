
#include "philo.h"

//subject specifically mentions.. philos shld avoid dying.. but also do not communicate...
//still need thinking condition? or handled by itself ?
void take_up_fork(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        print_status("has taken a fork", philo);
        pthread_mutex_lock(&philo->left_fork->fork);
        print_status("has taken a fork", philo);
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        print_status("has taken a fork", philo);
        pthread_mutex_lock(&philo->right_fork->fork);
        print_status("has taken a fork", philo);
    }
}

void eating(t_philo *philo)
{
    print_status("is eating", philo);

    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal_time = get_timestamp() - philo->symposium->start_symposium;
    pthread_mutex_unlock(&philo->meal_lock);
    

    philo->meals_counter++;
    //printf("\n### nb_meals:%lld - philo:%d ###\n", philo->meals_counter, philo->id); //!!!!!!!!!!!!!!!!!!!!!!dont print in final version
    if (philo->meals_counter == philo->symposium->n_meals)
    {
        pthread_mutex_lock(&philo->full_lock);
        philo->full = true;
        pthread_mutex_unlock(&philo->full_lock);
    }
    usleep(philo->symposium->time_to_eat);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}

void sleeping(t_philo *philo)
{
    print_status("is sleeping", philo);
    usleep(philo->symposium->time_to_sleep);
}

void thinking(t_philo *philo)
{
    //while (some condition until eat again)
    print_status("is thinking", philo);

}

void death(t_philo *philo)
{
    pthread_create(&philo->monitor_id, NULL, monitor_death, philo);
    pthread_detach(philo->monitor_id);
}
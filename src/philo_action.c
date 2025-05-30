
#include "philo.h"

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
    usleep(philo->symposium->time_to_eat);
    philo->last_meal_time = get_timestamp() - philo->symposium->start_symposium;
    philo->meals_counter++;
    if (philo->meals_counter == philo->symposium->n_meals)
        philo->full = true;
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
    pthread_create(&philo->monitor_id, NULL, monitor, philo);
    pthread_detach(philo->monitor_id);
}

#include "philo.h"

static void lonely_philo(t_philo *philo)
{
    print_status("has taken a fork", philo);
    ft_usleep(philo->symposium->time_to_die * 1000 + 10000, philo->symposium);
}

void take_up_fork(t_philo *philo)
{
    philo->left_fork_locked = false;
    philo->right_fork_locked = false;
    if (philo->symposium->n_philo == 1)
        lonely_philo(philo);
    else
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&philo->right_fork->fork);
            philo->right_fork_locked = true;
            print_status("has taken a fork", philo);
            pthread_mutex_lock(&philo->left_fork->fork);
            philo->left_fork_locked = true;
            print_status("has taken a fork", philo);
        }
        else
        {
            pthread_mutex_lock(&philo->left_fork->fork);
            philo->left_fork_locked = true;
            print_status("has taken a fork", philo);
            pthread_mutex_lock(&philo->right_fork->fork);
            philo->right_fork_locked = true;
            print_status("has taken a fork", philo);
        }
    }
}

int eating(t_philo *philo)
{
    long long now;

    now = get_timestamp((philo->symposium) - philo->symposium->start_symposium);
    if (now == -1)
        return (-1);
    print_status("is eating", philo);

    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal_time = now;
    pthread_mutex_unlock(&philo->meal_lock);
    ft_usleep(philo->symposium->time_to_eat, philo->symposium);

    pthread_mutex_unlock(&philo->left_fork->fork);
    philo->left_fork_locked = false;
    pthread_mutex_unlock(&philo->right_fork->fork);
    philo->right_fork_locked = false;

    philo->meals_counter++;
    if (philo->meals_counter == philo->symposium->n_meals)
    {
        pthread_mutex_lock(&philo->full_lock);
        philo->full = true;
        pthread_mutex_unlock(&philo->full_lock);
    }
    return (0);
}

void sleeping(t_philo *philo)
{
    print_status("is sleeping", philo);
    ft_usleep(philo->symposium->time_to_sleep, philo->symposium);
}

void thinking(t_philo *philo, bool pre_symposium)
{
    long long t_max;

    if (pre_symposium)
        print_status("is thinking", philo);

    if (philo->symposium->n_philo % 2 == 1)// && philo->id % 2 == 1)
    {
        t_max = (philo->symposium->time_to_die - (philo->symposium->time_to_eat + philo->symposium->time_to_sleep)) * 1000;
        if (t_max < 0)
            t_max = 0;
        ft_usleep(t_max / 2, philo->symposium);
    }
}



#include "philo.h"

void take_up_fork(t_philo *philo)
{

}

void eating(t_philo *philo)
{

}

void sleeping(t_philo *philo)
{

}

void thinking(t_philo *philo)
{

}

void death(t_philo *philo)
{
    pthread_create(&philo->monitor_id, NULL, monitor(), &philo);
    pthread_detach(&philo->monitor_id);

}

#include "philo.h"


static void init_philo(t_symposium *symposium)
{
    /*
    int         id;
    long long   meals_counter;
    bool        full;
    long long   last_meal_time; //he dead?

    t_fork      *right_fork;
    t_fork      *left_fork;
    pthread_t   thread_id; //needed to make philos threads
    t_symposium *symposium;
    */
    long long i;

    i = 0;
    while (symposium->n_philo > i) //possibly need to malloc arr of philos
    {   
        symposium->philo[i].id = i + 1;
        symposium->philo[i].meals_counter = 0;
        symposium->philo[i].full = false;
        symposium->philo[i].last_meal_time = 0; //??already initialize here?- check later usage tim eto die
        symposium->philo[i]->right_fork = //??some fork id - if philo[i].id = i % 2 //==odd then right fork first
        symposium->philo[i]->right_fork = //??some fork id - if !philo[i].id = i % 2 //==odd then left fork first
        pthread_create(symposium->philo[i].thread_id, NULL, "some_function", "some arg for function");
        symposium->philo[i].symposium = symposium;
    }

}

void init_symposium(t_symposium *symposium)
{
    /*
    X long long   start_symposium;
    X bool        finish_symposium; //death or all full
    //general handling
    t_philo *philo;
    t_fork *fork;

    ->
    t_mtx           fork;
    unsigned int    fork_id;
    */

    struct timeval tv;

    gettimeofday(&tv, NULL);
    symposium->start_symposium = (tv.tv_sec * 1000) + (tv.tv_usec * 1000);
    symposium->finish_symposium = false;

    //-----philos-----//
    init_philo(symposium);
   



}


#include "philo.h"

static bool is_digit(const char *str)
{
    return (*str >= '0' && *str <= '9');
}
static const char *valid_input(const char *s)
{
    const char *nbr;
    long long len;

    len = 0;
    while(*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    if (*s == '+')
        s++;
    else if (*s == '-')
        ft_error("No negative Input!\n");
    if (!is_digit(*s))
        ft_error("Input not a number\n");
    nbr = s;
    while (is_digit(*s++))
        len++;
    if (len > 10)
        ft_error("Input bigger than INT_MAX\n");
    return (nbr);
}

static const char *ft_atol(const char *s) 
{
    long long nb;

    nb = 0;
    s = valid_input(*s);

    while (is_digit(*s))
        nb = (nb * 10) + (*s++ - '0');
    if (nb > INT_MAX)
        ft_error("Input bigger than INT_MAX\n");
    return (nb);
}

void parse_symposium(t_symposium *init, int argc, char **argv)
{
    init->n_philo = ft_atol(argv[1]);
    init->time_to_die = ft_atol(argv[2]); //need msec but, usleep gets µsec
    init->time_to_eat = ft_atol(argv[3]); //need msec but, usleep gets µsec
    init->time_to_sleep = ft_atol(argv[4]); //need msec but, usleep gets µsec
    if (init->time_to_sleep < 6e4 || init->time_to_eat < 6e4 || init->time_to_die < 6e4)
        ft_error("Not enough time. Must be over 60ms\n");
    if (argv[5])
        init->n_need_to_eat = ft_atol(argv[5]);
    else
        init->n_need_to_eat = -1;
}
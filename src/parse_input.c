
#include "philo.h"

static bool is_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

static bool is_digit(char c)
{
    return ((c >= '0' && c <= '9'));
}


static const char *valid_input(const char *str)
{
    const char *number;
    int len;

    len = 0;
    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
    {
        printf("Only positive input is valid\n");
        return (NULL);
    }
    if (!is_digit(*str))
    {
        printf("Only digits input is valid\n");
        return (NULL);
    }
    number = str;
    while (is_digit(*str))
    {
        str++;
        len++;
    }
    if (len > 10)
    {
        printf("Overflow Warning\n");
        return (NULL);
    }
    return (number);
}

static long long ft_atol(const char *str, t_symposium *symposium)
{
    long long nb;

    nb = 0;
    if (!(str = valid_input(str)))
        return (-1);
    while (is_digit(*str))
        nb = (nb * 10) + (*str++ - '0');
    if (nb > INT_MAX)
        return(error_exit("Input larger than INT_MAX\n", symposium));
    return (nb);
}

int parse_input(t_symposium *symposium, int argc, char **argv)
{
    if ((symposium->n_philo = ft_atol(argv[1], symposium)) <= 0)
        return (1);
    if ((symposium->time_to_die = ft_atol(argv[2], symposium)) <= 60)
        return (error_exit("Time to die too small. Must be > 60ms due to OS limits", symposium));
    if ((symposium->time_to_eat = ft_atol(argv[3], symposium) * 1000) <= 6000)
        return (error_exit("Time to eat too small. Must be > 60ms due to OS limits", symposium));
    if ((symposium->time_to_sleep = ft_atol(argv[4], symposium) * 1000) <= 6000)
        return (error_exit("Time to sleep too small. Must be > 60ms due to OS limits", symposium));
    if (argc == 6)
    {
        if ((symposium->n_meals = ft_atol(argv[5], symposium)) <= 0)
            return (error_exit("Numvber of meals too small. Must be > 0", symposium));
    }
    else
        symposium->n_meals = -1;
    return (0);
}

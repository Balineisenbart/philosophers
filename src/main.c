
#include "philo.h"

int main(int argc, char **argv)
{
    t_symposium symposium;

    symposium.flag = false;
    if (argc < 5 || argc > 6)
        error_exit("Number of Input invalid\n", &symposium);
    else
    {
        symposium.flag = true;
        parse_input(&symposium, argc, argv);
        init_symposium(&symposium);
        start_symposium(&symposium);
        if (symposium.finish_symposium)
            clean_up(&symposium);
    }
    return (0);
}
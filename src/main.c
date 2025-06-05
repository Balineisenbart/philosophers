
#include "philo.h"

int main(int argc, char **argv)
{
    t_symposium symposium;

    symposium.flag = false;
    if (argc < 5 || argc > 6)
        return (error_exit("Number of Input invalid\n", &symposium));
    else
    {
        symposium.flag = true;
        parse_input(&symposium, argc, argv);
        init_symposium(&symposium);
        start_symposium(&symposium); //here routine is called & monitoring threads
        clean_up(&symposium); //routine joined
    }
    return (0);
}
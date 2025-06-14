
#include "philo.h"

int main(int argc, char **argv)
{
    t_symposium symposium;
    //in case of memory leak use memset to initialize all structs to 0

    symposium.flag = false;
    if (argc < 5 || argc > 6)
        return (error_exit("Number of Input invalid\n", &symposium));
    else
    {
        symposium.flag = true;
        if (parse_input(&symposium, argc, argv))
            return (1);
        if (init_symposium(&symposium))
            return (1);
        if (start_symposium(&symposium))
            return (1);
        if (clean_up(&symposium))
            return (1);
    }
    return (0);
}
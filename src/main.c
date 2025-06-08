
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
        return(parse_input(&symposium, argc, argv));
        return(init_symposium(&symposium));
        return(start_symposium(&symposium));
        return(clean_up(&symposium));
    }
    return (0);
}
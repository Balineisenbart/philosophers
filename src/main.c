
#include "philo.h"

/*
static void *detect_exit(void *arg)
{
    t_symposium *symposium = (t_symposium *)arg;
    while (1)
    {
        if (symposium->error_exit)
        {
            clean_up(symposium);
            printf("some error occured:\n");
            break;
        }
    }
    return (NULL);
}
*/

int main(int argc, char **argv)
{
    t_symposium symposium;
    //pthread_t   f_exit;

    symposium.flag = false;
    if (argc < 5 || argc > 6)
        return (error_exit("Number of Input invalid\n", &symposium));
    else
    {
        symposium.flag = true;
        parse_input(&symposium, argc, argv);
        init_symposium(&symposium);
        //pthread_create(&f_exit, NULL, detect_exit, &symposium);
        //pthread_detach(f_exit);
        //if (symposium.error_exit)
        //    return (1);
        start_symposium(&symposium);
        if (symposium.finish_symposium)
            clean_up(&symposium);
    }
    return (0);
}